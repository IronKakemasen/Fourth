$TargetFolder  = "C:\Users\yakii\OneDrive\文件\allForOne\Fourth\Project\Assets\Shader"

$RegistryFolder = "C:\Users\yakii\OneDrive\文件\allForOne\Fourth\Project\Assets\Registry"
$OutputFilePS  = "$RegistryFolder\PSFiles.txt"
$OutputFileMS  = "$RegistryFolder\MSFiles.txt"
$OutputFileCS  = "$RegistryFolder\CSFiles.txt"
$OutputFileOther= "$RegistryFolder\OtherFiles.txt"

if (-not (Test-Path $TargetFolder)) {
    Write-Error "指定されたターゲットフォルダが存在しません。"
    exit
}

if (-not (Test-Path $RegistryFolder)) {
    New-Item -ItemType Directory -Path $RegistryFolder | Out-Null
}

$assetsFolder = (Get-Item $TargetFolder).Parent.FullName
$projectFolder = (Get-Item $assetsFolder).Parent.FullName
$baseUri = New-Object System.Uri ($projectFolder + "\")

$linesPS    = @()
$linesMS    = @()
$linesCS    = @()
$linesOther = @()

$files = Get-ChildItem -Path $TargetFolder -Recurse -File

foreach ($file in $files) {
    if ($file.Extension -eq ".hlsli") {
        continue
    }

    $key = $file.BaseName
    
    $fileDirUri = New-Object System.Uri ($file.DirectoryName + "\")
    $relativeUri = $baseUri.MakeRelativeUri($fileDirUri)
    $value = [System.Uri]::UnescapeDataString($relativeUri.ToString())

    if ($value -eq "./" -or $value -eq ".") {
        $value = ""
    } elseif (-not $value.EndsWith("/")) {
        $value = $value + "/"
    }

    $line = "key: `"$key`" , value: `"$value`""

    if ($key -like "*PS*") {
        $linesPS += $line
    }
    elseif ($key -like "*MS*") {
        $linesMS += $line
    }
    elseif ($key -like "*CS*") {
        $linesCS += $line
    }
    else {
        $linesOther += $line
    }
}

if ($linesPS.Count -gt 0) {
    $linesPS | Out-File -FilePath $OutputFilePS -Encoding utf8
}
if ($linesMS.Count -gt 0) {
    $linesMS | Out-File -FilePath $OutputFileMS -Encoding utf8
}
if ($linesCS.Count -gt 0) {
    $linesCS | Out-File -FilePath $OutputFileCS -Encoding utf8
}
if ($linesOther.Count -gt 0) {
    $linesOther | Out-File -FilePath $OutputFileOther -Encoding utf8
}