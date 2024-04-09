using Windows.Foundation;
using Windows.Storage.Streams;

namespace MinGWComponent
{
    public sealed class ComponentClass
    {
        public int IntProperty { get; }
        public int Add(int a, int b);
        public IAsyncOperation<IRandomAccessStream> DownloadFileAsync(string url);
    }
}