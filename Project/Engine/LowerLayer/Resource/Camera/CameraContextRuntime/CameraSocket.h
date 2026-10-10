#pragma once

//厳密にいうと、バッファに書き込むカメラの接続口
//実際に更新・バッチングする必要のあるカメラはこのソケットに接続しているカメラのみということになる
//追加したら、CameraContext::CameraFrontlineSystems::Connectの明示的実体化も
enum class CameraSocket
{
	//メインカメラとデバッグカメラ共用。切り替え可能ということ
	kMainDebug,




	//この数分のカメラのバッファを作成する必要がある
	kCount
};


