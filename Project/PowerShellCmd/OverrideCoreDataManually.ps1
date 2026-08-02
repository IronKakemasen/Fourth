param(
    [string]$fileName,  # 1: JSONファイル名（.json なしでOK）
    [string]$groupName, # 2: グループ名
    [string]$keyName,   # 3: キー名
    [string]$value      # 4: 値（カンマ区切りで配列化）
)

# ------------------------------------------
# 余計なクォーテーションの自動除去 & スペース区切りの結合処理
# ------------------------------------------
if ($args.Count -gt 0) {
    $value = ($value, ($args -join " ")) -join " "
}

$fileName  = $fileName.Trim('"').Trim("'")
$groupName = $groupName.Trim('"').Trim("'")
$keyName   = $keyName.Trim('"').Trim("'")
if ($value) {
    $value = $value.Trim('"').Trim("'")
}

# ------------------------------------------
# 設定：保存先ディレクトリ
# ------------------------------------------
$baseDir = "C:\Users\yakii\OneDrive\文件\allForOne\Fourth\Project\Assets\JsonFiles\EngineCoreJsonFile"

if ([string]::IsNullOrWhiteSpace($fileName)) {
    Write-Host "エラー: JSONファイル名が指定されていません。" -ForegroundColor Red
    exit
}

if (-not $fileName.EndsWith(".json", [System.StringComparison]::OrdinalIgnoreCase)) {
    $fileName = "$fileName.json"
}

$filePath = Join-Path -Path $baseDir -ChildPath $fileName

# ------------------------------------------
# 型判別処理用の内部関数
# ------------------------------------------
function Parse-SingleValue([string]$item) {
    $item = $item.Trim()

    # 1. Bool値 (true / false)
    if ($item -match '^(true|false)$') {
        return [bool]::Parse($item)
    }
    # 2. Float値
    elseif ($item -match '^-?\d+\.\d+[fF]?$' -or $item -match '^-?\d+[fF]$') {
        $clean = $item -replace '[fF]$', ''
        return [double]$clean
    }
    # 3. 整数値
    elseif ($item -match '^-?\d+$') {
        return [int64]$item
    }
    # 4. 文字列
    return $item
}

# ------------------------------------------
# 値のパース処理（カンマが含まれていれば配列化）
# ------------------------------------------
if ($value -contains ',' -or $value -match ',') {
    # カンマで分割して要素ごとに型判別
    $parsedValue = @($value -split ',' | ForEach-Object { Parse-SingleValue $_ })
} else {
    $parsedValue = Parse-SingleValue $value
}

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
Write-Host " -> [$groupName][$keyName] = $value" -ForegroundColor Cyan