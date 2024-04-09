#include <cstdio>
#include <windows.h>
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/MinGWComponent.h>

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage::Streams;

int wmain() {
    auto c = winrt::MinGWComponent::ComponentClass{};
    printf("IntProperty = %d\n", c.IntProperty());
    printf("Add(1, 2) = %d\n", c.Add(1, 2));
    puts("");
    puts("Content of http://example.com: ");
    auto stream = c.DownloadFileAsync(L"http://example.com/").get();
    auto inputStream = stream.GetInputStreamAt(0);
    auto reader = DataReader{ inputStream };
    int bytesLoaded = reader.LoadAsync(stream.Size()).get();    
    auto str = reader.ReadString(bytesLoaded);
    _putws(str.c_str());
    return 0;
}
