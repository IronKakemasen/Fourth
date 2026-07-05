# ログファイルが溜まっているフォルダーのパス
$logFolder = "C:\Users\yakii\OneDrive\文件\allForOne\Fourth\Project\DebugLog"

# 一番新しい .log ファイルを探す
$latestLog = Get-ChildItem (Join-Path $logFolder "*.log") -ErrorAction SilentlyContinue | 
             Sort-Object LastWriteTime -Descending | 
             Select-Object -First 1

# ファイルが見つかったら開く
if ($latestLog) {
    Invoke-Item $latestLog.FullName
} else {
    # 見つからない場合は警告を表示して3秒待ってから自動で閉じます
    Write-Warning "【エラー】$logFolder に .log ファイルが見つかりませんでした。"
    Start-Sleep -Seconds 3
}