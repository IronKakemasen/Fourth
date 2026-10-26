#pragma once

//厳密にいうと、バッファに書き込むカメラの接続口
//実際に更新・バッチングする必要のあるカメラはこのソケットに接続しているカメラのみということになる
//追加したら、CameraContext::FrontlineSystems::Connectの明示的実体化も
enum class CameraSocket
{
	//デバッグカメラ
	kDebug,




	//この数分のカメラのバッファを作成する必要がある
	kCount
};


