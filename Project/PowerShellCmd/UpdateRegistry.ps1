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

        $key = $file.BaseName
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

        if ($key -like "*PS*")
        {
            $linesPS += $line
        }
        elseif ($key -like "*MS*")
        {
            $linesMS += $line
        }
        elseif ($key -like "*CS*")
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
# Texture Registry
########################################

$OutputFileTexture = Join-Path $RegistryFolder "TextureFiles.txt"
$TextureFolder = Join-Path $projectFolder "Assets\Texture"

if (Test-Path $OutputFileTexture)
{
    Remove-Item $OutputFileTexture
}

if (Test-Path $TextureFolder)
{
    Get-ChildItem -Path $TextureFolder -Recurse -File |
    Where-Object {
        $_.Extension.ToLower() -eq ".png" -or
        $_.Extension.ToLower() -eq ".jpg" -or
        $_.Extension.ToLower() -eq ".jpeg" -or
        $_.Extension.ToLower() -eq ".dds" -or
        $_.Extension.ToLower() -eq ".tga" -or
        $_.Extension.ToLower() -eq ".psd"
    } |
    ForEach-Object {

        # Texture フォルダから見た相対パス
        $relativeTexturePath = $_.FullName.Substring($TextureFolder.Length + 1)

        # 最初のフォルダ名を取得
        $parts = $relativeTexturePath -split '[\\/]'

        if ($parts.Count -ge 2)
        {
            $suffix = $parts[0]
            $key = "$($_.BaseName)_$suffix"
        }
        else
        {
            # Texture直下にあるファイルはファイル名のみ
            $key = $_.BaseName
        }

        # Projectフォルダからの相対パス
        $relativePath = $_.FullName.Substring($projectFolder.Length + 1).Replace("\", "/")

        Add-Content -Path $OutputFileTexture -Value "key: `"$key`" , value: `"$relativePath`""
    }
}

########################################
# Update TextureSettings.json
########################################

# TextureSettings.json のパス
$TextureSettingsPath = Join-Path $projectFolder "Assets\JsonFiles\AssetsJsonFile\TextureSettings.json"

# 保存先フォルダ作成
$textureSettingsDir = Split-Path -Path $TextureSettingsPath -Parent

if (-not (Test-Path $textureSettingsDir))
{
    New-Item -ItemType Directory -Path $textureSettingsDir -Force | Out-Null
}

# TextureSettings の既存データ
$textureSettingsDict = [ordered]@{}

# 既存 TextureSettings.json を読み込み
if (Test-Path $TextureSettingsPath)
{
    $rawTextureSettings = Get-Content -Path $TextureSettingsPath -Raw -Encoding UTF8

    if (-not [string]::IsNullOrWhiteSpace($rawTextureSettings))
    {
        try
        {
            $parsedTextureSettings = $rawTextureSettings | ConvertFrom-Json

            if ($parsedTextureSettings -is [PSCustomObject])
            {
                foreach ($prop in $parsedTextureSettings.psobject.Properties)
                {
                    $textureSettingsDict[$prop.Name] = $prop.Value
                }
            }
        }
        catch
        {
            Write-Warning "TextureSettings.json の読み込みに失敗したため、既存データを変更せず処理を中止します。"
            $textureSettingsDict = $null
        }
    }
}

# JSON が壊れている場合は既存データを上書きしない
if ($null -ne $textureSettingsDict)
{
    $isTextureSettingsUpdated = $false

    # TextureFiles.txt に登録されているキーを確認
    if (Test-Path $OutputFileTexture)
    {
        $textureLines = Get-Content -Path $OutputFileTexture -Encoding UTF8

        foreach ($textureLine in $textureLines)
        {
            # key: "Sample_albedo" , value: "Assets/Texture/albedo/Sample.png"
            if ($textureLine -match 'key:\s*"([^"]+)"')
            {
                $textureKey = $Matches[1]

                # 既に登録済みなら何もしない
                if ($textureSettingsDict.Contains($textureKey))
                {
                    continue
                }

                # 最後の "_" より後ろを TextureType として取得
                $textureType = ""

                $lastUnderscoreIndex = $textureKey.LastIndexOf("_")

                if ($lastUnderscoreIndex -ge 0 -and
                    $lastUnderscoreIndex -lt ($textureKey.Length - 1))
                {
                    $textureType = $textureKey.Substring($lastUnderscoreIndex + 1)
                }

                # 未登録テクスチャのデフォルト設定
                $textureSettingsDict[$textureKey] = [ordered]@{
                    "TextureType" = $textureType
                    "Quality"     = "High"
                }

                $isTextureSettingsUpdated = $true

                Write-Host "TextureSettings 追加: $textureKey"
            }
        }
    }

    # 新規登録があった場合のみ保存
    if ($isTextureSettingsUpdated -or -not (Test-Path $TextureSettingsPath))
    {
        $textureJsonOutput = $textureSettingsDict | ConvertTo-Json -Depth 100

        $utf8NoBom = New-Object System.Text.UTF8Encoding($false)
        [System.IO.File]::WriteAllText(
            $TextureSettingsPath,
            $textureJsonOutput,
            $utf8NoBom
        )
    }
}
