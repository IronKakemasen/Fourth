#pragma once
#include <atomic>

class IncludeHandler : public IDxcIncludeHandler
{
public:
    IncludeHandler(Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils_, std::wstring baseDir_)
        : dxcUtils(dxcUtils_), baseDir(std::move(baseDir_))
    {
        // baseDirの末尾にスラッシュが無ければ足しておく
        if (!baseDir.empty() && baseDir.back() != L'/' && baseDir.back() != L'\\')
        {
            baseDir += L'/';
        }
    }

    HRESULT STDMETHODCALLTYPE LoadSource(LPCWSTR pFilename, IDxcBlob** ppIncludeSource) override
    {

        OutputDebugStringW(L"LoadSource called: ");
        OutputDebugStringW(pFilename);
        OutputDebugStringW(L"\n");

        std::wstring requested = pFilename;

        // 先頭の "./" を除去（DXCがつけてくることがある）
        if (requested.rfind(L"./", 0) == 0)
        {
            requested = requested.substr(2);
        }

        // "../" や "/" が含まれていても、ファイル名部分だけを取り出す
        size_t lastSlash = requested.find_last_of(L"/\\");
        std::wstring fileNameOnly = (lastSlash == std::wstring::npos)
            ? requested
            : requested.substr(lastSlash + 1);

        std::wstring fullPath = baseDir + fileNameOnly;

        Microsoft::WRL::ComPtr<IDxcBlobEncoding> encoding;
        HRESULT hr = dxcUtils->LoadFile(fullPath.c_str(), nullptr, &encoding);

        OutputDebugStringW(L"fullPath: ");
        OutputDebugStringW(fullPath.c_str());
        OutputDebugStringW(hr == S_OK ? L" -> OK\n" : L" -> FAILED\n");

        if (FAILED(hr))
        {
            // 見つからなかった場合、DXC側がfile not foundとして扱ってくれる
            *ppIncludeSource = nullptr;
            return E_FAIL;
        }

        HRESULT copyHr = encoding.CopyTo(ppIncludeSource);
        OutputDebugStringW(copyHr == S_OK ? L"CopyTo -> OK\n" : L"CopyTo -> FAILED\n");

        return encoding.CopyTo(ppIncludeSource);
    }

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override
    {
        if (riid == __uuidof(IDxcIncludeHandler) || riid == __uuidof(IUnknown))
        {
            *ppvObject = static_cast<IDxcIncludeHandler*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    ULONG STDMETHODCALLTYPE AddRef() override
    {
        return ++refCount;
    }

    ULONG STDMETHODCALLTYPE Release() override
    {
        ULONG result = --refCount;
        if (result == 0) delete this;
        return result;
    }

private:
    std::atomic<ULONG> refCount = 1;
    Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils;
    std::wstring baseDir;
};