#include "MinGWComponent.ComponentClass.h"

#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Web.Http.h>

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Web::Http;

namespace winrt::MinGWComponent::implementation
{
    int32_t ComponentClass::IntProperty()
    {
        return 42;
    }
    int32_t ComponentClass::Add(int32_t a, int32_t b)
    {
        return a + b;
    }
    IAsyncOperation<IRandomAccessStream> ComponentClass::DownloadFileAsync(hstring url)
    {
        auto httpClient = HttpClient{};
        auto result = co_await httpClient.TryGetAsync(Uri {url});
        auto stream = InMemoryRandomAccessStream{};
        co_await result.ResponseMessage().Content().WriteToStreamAsync(stream);
        stream.Seek(0);
        co_return stream;
    }
}
