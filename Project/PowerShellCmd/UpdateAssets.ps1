# ==============================================================================
# Generate Registry Files
# ==============================================================================

# --- 1. プロジェクトルートフォルダ（Assetsが存在する階層）の自動検出 ---
$currentDir = if ($PSScriptRoot) { $PSScriptRoot } else { (Get-Location).Path }
$projectFolder = $currentDir

while ($projectFolder -and -not (Test-Path (Join-Path $projectFolder "Assets")))
{
    $parent = Split-Path -Path $projectFolder -Parent
    if ($parent -eq $projectFolder) { break }
    $projectFolder = $parent
}

if (-not (Test-Path (Join-Path $projectFolder "Assets")))
{
    $projectFolder = $currentDir
}

# パス定義
$RegistryFolder     = Join-Path $projectFolder "Assets\Registry"
$ShaderFolder       = Join-Path $projectFolder "Assets\Shader"
$ModelFolder        = Join-Path $projectFolder "Assets\Model"
$JsonFolder         = Join-Path $projectFolder "Assets\JsonFiles"
$ShaderSettingsPath = Join-Path $projectFolder "Assets\JsonFiles\AssetsJsonFile\ShaderSettings.json"


# Registry フォルダ作成
if (-not (Test-Path $RegistryFolder))
{
    New-Item -ItemType Directory -Path $RegistryFolder -Force | Out-Null
}



########################################
# Shader Registry
########################################

$OutputFilePS = Join-Path $RegistryFolder "PSFiles.txt"
$OutputFileMS = Join-Path $RegistryFolder "MSFiles.txt"
$OutputFileCS = Join-Path $RegistryFolder "CSFiles.txt"

$linesPS = @()
$linesMS = @()
$linesCS = @()

$registeredShaderKeys = New-Object System.Collections.ArrayList


if (Test-Path $ShaderFolder)
{
    $baseUri = New-Object System.Uri ($projectFolder + "\")
    $files   = Get-ChildItem -Path $ShaderFolder -Recurse -File

    foreach ($file in $files)
    {
        # hlsli除外
        if ($file.Extension.ToLower() -eq ".hlsli")
        {
            continue
        }

        $folderName = $file.Directory.Name
        $key = $file.BaseName + $folderName
        if (-not $registeredShaderKeys.Contains($key))
        {
            $null = $registeredShaderKeys.Add($key)
        }

        $fileDirUri  = New-Object System.Uri ($file.DirectoryName + "\")
        $relativeUri = $baseUri.MakeRelativeUri($fileDirUri)
        $value       = [System.Uri]::UnescapeDataString($relativeUri.ToString())

        if ($value -eq "./" -or $value -eq ".")
        {
            $value = ""
        }
        elseif (-not $value.EndsWith("/"))
        {
            $value += "/"
        }

        $line = "key: `"$key`" , value: `"$value`""

        if ($folderName -eq "PS")
        {
            $linesPS += $line
        }
        elseif ($folderName -eq "MS")
        {
            $linesMS += $line
        }
        elseif ($folderName -eq "CS")
        {
            $linesCS += $line
        }
    }

    $linesPS | Out-File -FilePath $OutputFilePS -Encoding utf8
    $linesMS | Out-File -FilePath $OutputFileMS -Encoding utf8
    $linesCS | Out-File -FilePath $OutputFileCS -Encoding utf8
}



########################################
# Update ShaderSettings.json
########################################

$shaderSettingsDir = Split-Path -Path $ShaderSettingsPath -Parent
if (-not (Test-Path $shaderSettingsDir))
{
    New-Item -ItemType Directory -Path $shaderSettingsDir -Force | Out-Null
}

$shaderDict = [ordered]@{}

# 既存データのロード
if (Test-Path $ShaderSettingsPath)
{
    $rawShaderSettings = Get-Content -Path $ShaderSettingsPath -Raw -Encoding UTF8
    if (-not [string]::IsNullOrWhiteSpace($rawShaderSettings))
    {
        try
        {
            $parsed = $rawShaderSettings | ConvertFrom-Json
            if ($parsed -is [PSCustomObject])
            {
                foreach ($prop in $parsed.psobject.Properties)
                {
                    $shaderDict[$prop.Name] = $prop.Value
                }
            }
        }
        catch
        {
            Write-Warning "ShaderSettings.json の読み込みに失敗したため再構築します。"
        }
    }
}

# キーが存在しないシェーダーのみ "Args": ["none"] を追加
$isUpdated = $false
foreach ($shaderKey in $registeredShaderKeys)
{
    if (-not $shaderDict.Contains($shaderKey))
    {
        $shaderDict[$shaderKey] = [ordered]@{
            "Args" = @("none")
        }
        $isUpdated = $true
    }
}

# 変更があった場合のみ保存
if ($isUpdated -or -not (Test-Path $ShaderSettingsPath))
{
    $jsonOutput = $shaderDict | ConvertTo-Json -Depth 100
    if (-not [string]::IsNullOrWhiteSpace($jsonOutput) -and $jsonOutput -ne "{}")
    {
        $jsonOutput = [regex]::Replace($jsonOutput, '"Args":\s*"([^"]*)"', '"Args": [ "$1" ]')
    }

    $utf8NoBom = New-Object System.Text.UTF8Encoding($false)
    [System.IO.File]::WriteAllText($ShaderSettingsPath, $jsonOutput, $utf8NoBom)
}



########################################
# Model Registry
########################################

$OutputFileModel = Join-Path $RegistryFolder "ModelFiles.txt"

if (Test-Path $OutputFileModel)
{
    Remove-Item $OutputFileModel
}

if (Test-Path $ModelFolder)
{
    Get-ChildItem -Path $ModelFolder -Recurse -File |
    Where-Object {
        $_.Extension.ToLower() -eq ".obj" -or
        $_.Extension.ToLower() -eq ".gltf"
    } |
    ForEach-Object {

        $name = $_.BaseName

        switch ($_.Extension.ToLower())
        {
            ".obj"  { $suffix = "Obj" }
            ".gltf" { $suffix = "Gltf" }
        }

        $key          = $name + $suffix
        $relativePath = $_.FullName.Substring($projectFolder.Length + 1).Replace("\", "/")

        Add-Content -Path $OutputFileModel -Value "key: `"$key`" , value: `"$relativePath`""
    }
}



########################################
# JSON Registry
########################################

$OutputFileJson = Join-Path $RegistryFolder "JsonFiles.txt"

if (Test-Path $OutputFileJson)
{
    Remove-Item $OutputFileJson
}

if (Test-Path $JsonFolder)
{
    Get-ChildItem -Path $JsonFolder -Recurse -File |
    Where-Object {
        $_.Extension.ToLower() -eq ".json"
    } |
    ForEach-Object {

        # JsonFiles.txt へのパス登録のみ実施
        $key          = $_.BaseName
        $relativePath = $_.FullName.Substring($projectFolder.Length + 1).Replace("\", "/")

        Add-Content -Path $OutputFileJson -Value "key: `"$key`" , value: `"$relativePath`""
    }
}



########################################
# Texture Compile (Original & Model -> Compiled)
########################################

$TexConvPath       = Join-Path $projectFolder "texconv.exe"
$TextureOriginal   = Join-Path $projectFolder "Assets\Texture\Original"
$TextureCompiled   = Join-Path $projectFolder "Assets\Texture\Compiled"

$TextureFormatMap = @{
    "albedo"   = "BC7_UNORM_SRGB"
    "normal"   = "BC5_UNORM"
    "sprite"   = "BC7_UNORM_SRGB"
    "emissive" = "BC7_UNORM_SRGB"
}

if (-not (Test-Path -LiteralPath $TexConvPath))
{
    throw "texconv.exe が見つかりません: $TexConvPath"
}

New-Item -ItemType Directory -Path $TextureCompiled -Force | Out-Null
$compiledNames = New-Object 'System.Collections.Generic.HashSet[string]' ([System.StringComparer]::OrdinalIgnoreCase)

# 検索対象ファイルを一括収集（参照元区分を保持）
$targets = @()

if (Test-Path -LiteralPath $TextureOriginal)
{
    Get-ChildItem -Path $TextureOriginal -Recurse -File |
        Where-Object { $_.Extension -ceq ".png" -or $_.Extension -ceq ".jpg" } |
        ForEach-Object {
            $targets += [PSCustomObject]@{ File = $_; Source = "Original" }
        }
}

if (Test-Path -LiteralPath $ModelFolder)
{
    Get-ChildItem -Path $ModelFolder -Recurse -File |
        Where-Object { $_.Extension -ceq ".png" -or $_.Extension -ceq ".jpg" } |
        ForEach-Object {
            $targets += [PSCustomObject]@{ File = $_; Source = "Model" }
        }
}

foreach ($item in $targets)
{
    $file   = $item.File
    $source = $item.Source
    $category = $null

    if ($source -eq "Original")
    {
        # Original: 直下フォルダ名からカテゴリ取得
        $relativeToOriginal = $file.FullName.Substring($TextureOriginal.Length).TrimStart('\')
        $relativeParts      = $relativeToOriginal -split '[\\/]'
        $category           = $relativeParts[0].ToLower()
    }
    else
    {
        # Model: ファイル名の末尾（_albedo, _normal 等）からカテゴリ検出
        foreach ($key in $TextureFormatMap.Keys)
        {
            if ($file.BaseName.ToLower() -like "*_$key")
            {
                $category = $key
                break
            }
        }
    }

    # 対応外カテゴリは警告してスキップ
    if (-not $category -or -not $TextureFormatMap.ContainsKey($category))
    {
        Write-Warning "対応外フォルダまたは未対応の命名規則のためスキップ: $($file.FullName)"
        continue
    }

    # DDS出力ファイル名の生成（二重付与を防止）
    $baseNameLower = $file.BaseName.ToLower()
    if ($baseNameLower.EndsWith("_$category"))
    {
        $outputName = "{0}.dds" -f $file.BaseName
    }
    else
    {
        $outputName = "{0}_{1}.dds" -f $file.BaseName, $category
    }

    $outputPath = Join-Path $TextureCompiled $outputName

    # 既存ファイルおよび同名競合のスキップ
    if (Test-Path -LiteralPath $outputPath)
    {
        Write-Host "既存ファイルのためスキップ: $outputName"
        continue
    }

    if (-not $compiledNames.Add($outputName))
    {
        Write-Warning "同名衝突のためスキップ: $($file.FullName) -> $outputName"
        continue
    }

    $format   = $TextureFormatMap[$category]
    $mipCount = if ($category -ceq "sprite") { "1" } else { "0" }

    # 一時フォルダ作成と DDS 変換処理
    $tempDir = Join-Path $TextureCompiled (".texconv_tmp_{0}" -f ([guid]::NewGuid().ToString("N")))
    New-Item -ItemType Directory -Path $tempDir -Force | Out-Null

    try
    {
        Write-Host "DDS変換中 ($source): $($file.FullName) -> $outputName"

        & $TexConvPath `
            -y `
            -ft dds `
            -f $format `
            -m $mipCount `
            -o $tempDir `
            $file.FullName

        if ($LASTEXITCODE -ne 0)
        {
            throw "DDS変換に失敗しました: $($file.FullName)"
        }

        $generatedFile = Get-ChildItem -LiteralPath $tempDir -File |
            Where-Object { $_.Extension -ieq ".dds" } |
            Select-Object -First 1

        if ($null -eq $generatedFile)
        {
            throw "texconvの出力ファイルが見つかりません: $($file.FullName)"
        }

        Move-Item `
            -LiteralPath $generatedFile.FullName `
            -Destination $outputPath
    }
    finally
    {
        if (Test-Path -LiteralPath $tempDir)
        {
            Remove-Item -LiteralPath $tempDir -Recurse -Force
        }
    }
}



########################################
# Texture Registry
########################################

$OutputFileTexture = Join-Path $RegistryFolder "TextureFiles.txt"
$TextureFolder = Join-Path $projectFolder "Assets\Texture\Compiled"

if (Test-Path $OutputFileTexture)
{
    Remove-Item $OutputFileTexture
}

if (Test-Path $TextureFolder)
{
    Get-ChildItem -Path $TextureFolder -Recurse -File |
    Where-Object {
               $_.Extension.ToLower() -eq ".dds"
    } |
    ForEach-Object {

        # サブフォルダ名による接尾辞を廃止し、ファイル名をそのままキーに使用
        $key = $_.BaseName

        # Projectフォルダからの相対パス
        $relativePath = $_.FullName.Substring($projectFolder.Length + 1).Replace("\", "/")

        Add-Content -Path $OutputFileTexture -Value "key: `"$key`" , value: `"$relativePath`""
    }
}