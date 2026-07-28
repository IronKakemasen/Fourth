param(
    [string]$fileName,  # 1: JSONファイル名（.json なしでOK）
    [string]$groupName, # 2: グループ名
    [string]$keyName,   # 3: キー名
    [string]$value      # 4: 値（自動型判別）
)

# ------------------------------------------
# 設定：保存先ディレクトリ
# ------------------------------------------
$baseDir = "C:\Users\yakii\OneDrive\文件\allForOne\Fourth\Project\Assets\JsonFiles\EngineCoreJsonFile"
# ファイル名チェック
if ([string]::IsNullOrWhiteSpace($fileName)) {
    Write-Host "エラー: JSONファイル名が指定されていません。" -ForegroundColor Red
    exit
}

# 拡張子 .json の自動補完
if (-not $fileName.EndsWith(".json", [System.StringComparison]::OrdinalIgnoreCase)) {
    $fileName = "$fileName.json"
}

# フルパスを作成
$filePath = Join-Path -Path $baseDir -ChildPath $fileName

# ------------------------------------------
# 型の自動判別（Bool / Float / Int / String）
# ------------------------------------------
$parsedValue = $value

# 1. Bool値 (true / false)
if ($value -match '^(true|false)$') {
    $parsedValue = [bool]::Parse($value)
}
# 2. Float値（3.14 や -0.5 に加え、1.0f や 2f などの 'f' 付き表記にも対応）
elseif ($value -match '^-?\d+\.\d+[fF]?$' -or $value -match '^-?\d+[fF]$') {
    $cleanValue = $value -replace '[fF]$', ''
    $parsedValue = [double]$cleanValue
}
# 3. 整数値 (100, -50 など)
elseif ($value -match '^-?\d+$') {
    $parsedValue = [int64]$value
}
# 4. それ以外は文字列 ($value のまま)

# ------------------------------------------
# 1. 保存先フォルダが存在しなければ自動作成
# ------------------------------------------
if (-not (Test-Path -Path $baseDir)) {
    New-Item -ItemType Directory -Path $baseDir -Force | Out-Null
}

# ------------------------------------------
# 2. ファイルが存在すれば読み込み、無ければ新規作成
# ------------------------------------------
if (Test-Path -Path $filePath) {
    $rawText = Get-Content -Path $filePath -Raw -Encoding UTF8
    $jsonObj = if ([string]::IsNullOrWhiteSpace($rawText)) { [PSCustomObject]@{} } else { $rawText | ConvertFrom-Json }
} else {
    $jsonObj = [PSCustomObject]@{}
}

# ------------------------------------------
# 3. グループを追加（無ければ作成）
# ------------------------------------------
if (-not ($jsonObj.PSObject.Properties[$groupName])) {
    $jsonObj | Add-Member -NotePropertyName $groupName -NotePropertyValue ([PSCustomObject]@{})
}

# ------------------------------------------
# 4. バリューを登録（型を判別した値で上書き）
# ------------------------------------------
$jsonObj.$groupName | Add-Member -NotePropertyName $keyName -NotePropertyValue $parsedValue -Force

# ------------------------------------------
# 5. UTF-8 で保存
# ------------------------------------------
$jsonObj | ConvertTo-Json -Depth 10 | Set-Content -Path $filePath -Encoding UTF8

Write-Host "JSON更新完了: $filePath" -ForegroundColor Green
Write-Host " -> [$groupName][$keyName] = $parsedValue ($($parsedValue.GetType().Name))" -ForegroundColor Cyan