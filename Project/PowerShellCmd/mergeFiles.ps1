$targetPath = "C:\Users\yakii\OneDrive\文件\allForOne\Fourth\Project\Engine"
$outputPath = Join-Path $args[0] "all_files.txt"

$utf8NoBOM = New-Object System.Text.UTF8Encoding($false)
$writer = New-Object System.IO.StreamWriter($outputPath, $false, $utf8NoBOM)

# カウント用変数
$totalFiles = 0
$effectiveLines = 0

Get-ChildItem $targetPath -Recurse | ForEach-Object {
    if (!$_.PSIsContainer) {
        $totalFiles++

        $writer.WriteLine("========================================")
        $writer.WriteLine("=== FILE: $($_.FullName) ===")
        $writer.WriteLine("========================================")

        $lines = [System.IO.File]::ReadAllLines($_.FullName)
        foreach ($line in $lines) {
            # 1. 空白行は出力テキスト自体から除外
            if (![string]::IsNullOrWhiteSpace($line)) {
                $writer.WriteLine($line)

                # 2. 行頭の空白を除去してコメント行判定（// または #）
                $trimmed = $line.Trim()
                $isComment = $trimmed.StartsWith("//") -or $trimmed.StartsWith("#")

                # コメント行でなければ有効行数としてカウント
                if (!$isComment) {
                    $effectiveLines++
                }
            }
        }
        $writer.WriteLine()
    }
}

# 末尾に集計結果を出力
$writer.WriteLine("========================================")
$writer.WriteLine("=== SUMMARY ===")
$writer.WriteLine("========================================")
$writer.WriteLine("Total Files      : $totalFiles")
$writer.WriteLine("Effective Lines  : $effectiveLines")

$writer.Close()