# ========================================
# Generate Registry Files
# ========================================

if ($PSScriptRoot)
{
    $projectFolder = (Resolve-Path "$PSScriptRoot\..").Path
}
else
{
    $projectFolder = (Get-Location).Path
}


$RegistryFolder = Join-Path $projectFolder "Assets\Registry"

$ShaderFolder = Join-Path $projectFolder "Assets\Shader"
$ModelFolder  = Join-Path $projectFolder "Assets\Model"


# Registryフォルダ作成
if (-not (Test-Path $RegistryFolder))
{
    New-Item -ItemType Directory -Path $RegistryFolder | Out-Null
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


if (Test-Path $ShaderFolder)
{
    $baseUri = New-Object System.Uri ($projectFolder + "\")

    $files = Get-ChildItem `
        -Path $ShaderFolder `
        -Recurse `
        -File


    foreach ($file in $files)
    {
        # hlsli除外
        if ($file.Extension -eq ".hlsli")
        {
            continue
        }


        $key = $file.BaseName


        $fileDirUri = New-Object System.Uri (
            $file.DirectoryName + "\"
        )

        $relativeUri = $baseUri.MakeRelativeUri(
            $fileDirUri
        )


        $value = [System.Uri]::UnescapeDataString(
            $relativeUri.ToString()
        )


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


    $linesPS | Out-File `
        -FilePath $OutputFilePS `
        -Encoding utf8

    $linesMS | Out-File `
        -FilePath $OutputFileMS `
        -Encoding utf8

    $linesCS | Out-File `
        -FilePath $OutputFileCS `
        -Encoding utf8
}



########################################
# Model Registry
########################################

$OutputFileModel = Join-Path `
    $RegistryFolder `
    "ModelFiles.txt"


if (Test-Path $OutputFileModel)
{
    Remove-Item $OutputFileModel
}


if (Test-Path $ModelFolder)
{
    Get-ChildItem `
        -Path $ModelFolder `
        -Recurse `
        -File |
    Where-Object {
        $_.Extension -eq ".obj" -or
        $_.Extension -eq ".gltf"
    } |
    ForEach-Object {

        $name = $_.BaseName


        switch ($_.Extension.ToLower())
        {
            ".obj"
            {
                $suffix = "Obj"
            }

            ".gltf"
            {
                $suffix = "Gltf"
            }
        }


        $key = $name + $suffix


        $relativePath = $_.FullName.Substring(
            $projectFolder.Length + 1
        )


        $relativePath = $relativePath.Replace(
            "\",
            "/"
        )


        Add-Content `
            -Path $OutputFileModel `
            -Value "key: `"$key`" , value: `"$relativePath`""
    }
}



Write-Host ""
Write-Host "Registry generated successfully."
Write-Host $RegistryFolder