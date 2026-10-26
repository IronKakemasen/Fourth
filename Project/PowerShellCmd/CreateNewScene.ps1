param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$sceneName  # シーン名（.json は省略可能）
)

$ErrorActionPreference = "Stop"

# シーン名を整形し、ファイル名として不正な文字やパス指定を拒否する
$sceneName = $sceneName.Trim().Trim('"').Trim("'")
if ([string]::IsNullOrWhiteSpace($sceneName)) {
    Write-Host "エラー: シーン名を指定してください。" -ForegroundColor Red
    exit 1
}

if ($sceneName.EndsWith(".json", [System.StringComparison]::OrdinalIgnoreCase)) {
    $sceneName = $sceneName.Substring(0, $sceneName.Length - 5)
}

if ([string]::IsNullOrWhiteSpace($sceneName) -or
    $sceneName.IndexOfAny([System.IO.Path]::GetInvalidFileNameChars()) -ge 0 -or
    $sceneName.Contains("/") -or $sceneName.Contains("\")) {
    Write-Host "エラー: シーン名にファイル名として使用できない文字が含まれています。" -ForegroundColor Red
    exit 1
}

# スクリプトの場所から親ディレクトリをたどり、Assets フォルダを持つ
# プロジェクトディレクトリを探す。ユーザー固有の絶対パスには依存しない。
$currentDir = Get-Item -LiteralPath $PSScriptRoot
$projectRoot = $null

while ($null -ne $currentDir) {
    $assetsPath = Join-Path $currentDir.FullName "Assets"
    if (Test-Path -LiteralPath $assetsPath -PathType Container) {
        $projectRoot = $currentDir.FullName
        break
    }
    $currentDir = $currentDir.Parent
}

if ($null -eq $projectRoot) {
    Write-Host "エラー: スクリプトの親ディレクトリから Assets フォルダを見つけられませんでした。" -ForegroundColor Red
    Write-Host "このスクリプトをプロジェクト内、またはその配下のディレクトリに配置してください。" -ForegroundColor Yellow
    exit 1
}

# 相対パス: <プロジェクトルート>\Assets\JsonFiles\SceneData
$baseDir = Join-Path $projectRoot "Assets\JsonFiles\SceneData"
$filePath = Join-Path $baseDir "$sceneName.json"

if (-not (Test-Path -LiteralPath $baseDir -PathType Container)) {
    New-Item -ItemType Directory -Path $baseDir -Force | Out-Null
}

# 既存ファイルを誤って上書きしない
if (Test-Path -LiteralPath $filePath) {
    Write-Host "エラー: ファイルは既に存在します: $filePath" -ForegroundColor Red
    exit 1
}

$jsonTemplate = @'
{
    "GameObjectUpdatePriority":
    [

    ]
}
'@

# UTF-8（BOM なし）で保存
$utf8NoBom = New-Object System.Text.UTF8Encoding($false)
[System.IO.File]::WriteAllText($filePath, $jsonTemplate + [Environment]::NewLine, $utf8NoBom)

Write-Host "シーンデータのデフォルトJSONを作成しました: $filePath" -ForegroundColor Green
