$targetPath = "C:\Users\yakii\OneDrive\文件\allForOne\Fourth\Project\Engine"
$outputPath = Join-Path $args[0] "all_files.txt"

$utf8NoBOM = New-Object System.Text.UTF8Encoding($false)
$writer = New-Object System.IO.StreamWriter($outputPath, $false, $utf8NoBOM)

Get-ChildItem $targetPath -Recurse | ForEach-Object {
    if (!$_.PSIsContainer) {
        $writer.WriteLine("========================================")
        $writer.WriteLine("=== FILE: $($_.FullName) ===")
        $writer.WriteLine("========================================")
        $content = [System.IO.File]::ReadAllText($_.FullName)
        $writer.WriteLine($content)
        $writer.WriteLine("`n`n")
    }
}
$writer.Close()