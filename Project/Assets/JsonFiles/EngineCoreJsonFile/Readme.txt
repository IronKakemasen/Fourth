RenderPassSettings

Render Passごとの設定を記述する。

【基本設定】

isOffScreen : bool
オフスクリーンパスかどうか。falseの場合、ms / psは省略可能。

ms : string
使用するメッシュシェーダー名。

ps : string
使用するピクセルシェーダー名。


【カラーバッファ】

※すべて配列形式で指定する。

doesOwnColorBuffers: bool
自前のカラーバッファを所持するかどうか

ownedColorBufferNames : string[]
そのパスが所持するカラーバッファ名。

blendModes : string[]
ブレンドモードenumを文字列で指定。kDependsModelはモデル依存。

colorFormats : int[]
カラーフォーマット。

clearColors : double[][]
Clear時の色をRGBWで指定。

colorWidths : int[]
カラーバッファの幅。-1にしてくれれば、ウィンドウサイズと認識します

colorHeights : int[]
カラーバッファの高さ。同上

numBuffer_Colors : int[]
バッファ数。シングル / ダブルを指定。


【深度バッファ】

useDepthStencilがfalseの場合、以下の項目は省略可能。

useDepthStencil : bool
深度バッファを使用するかどうか。

depthBufferName : string
深度バッファ名。

dsvFormat : int
DSVフォーマット。

srvFormat : int
SRVフォーマット。

clearDepth : double
Clear時のDepth値。

clearStencilFlag : bool
stencilをクリアするかどうか

clearStencil : int
Clear時のStencil値。

depthWidth : int
深度バッファの幅。-1にしてくれれば、ウィンドウサイズと認識します

depthHeight : int
深度バッファの高さ。同上

numBuffer_Depth : int
バッファ数。シングル / ダブルを指定。


【深度設定】

depthTest : int
RenderPassComponent::DepthTestを参照。

depthEnable : bool
深度テストを有効にするかどうか。

depthBias : int
Depth Bias。

depthBiasClamp : double
Depth Bias Clamp。

slopeScaledDepthBias : double
Slope Scaled Depth Bias。


【参照バッファ】

referenceBufferNames : string[]
HLSLで参照するバッファの名前。


【書き込みシェアするバッファ】

カラーバッファ
writeSharingColorBufferNames : string[]
深度バッファ
writeSharingDepthBufferName : string