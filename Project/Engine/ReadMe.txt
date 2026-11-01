Diplomatの概念

Diplomat
|
|
|-CmdProvider   
|
|
|-ToolLender
|
|
|-ExecutionAgent


CmdProvider		...コマンドを"保持したい"パターンなどで経由。多少の結合度が強くなるのは仕方なし

ToolLender		...コマンドにするにはオーバーヘッドが気になるケースで経由。結合度を疎にしやすい

ExecutionAgent	..."保持する必要が無い"ケースで経由。特定のクラスでのみなどの限定的なケースではこちら
で対応したい。そのコンテキスト内で多少の結合度が強くなるのは仕方なし
