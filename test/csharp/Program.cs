using MinGWComponent;

namespace MinGWComponentTest;

public static class Program
{
    public static async Task Main(string[] args)
    {
        var component = new ComponentClass();        
        Console.WriteLine($"IntProperty = {component.IntProperty}");
        Console.WriteLine($"Add(1, 2) = {component.Add(1, 2)}");
        Console.WriteLine();
        Console.WriteLine("Content of http://example.com: ");
        using var randomAccessStream = await component.DownloadFileAsync("https://example.com");
        using var reader = new StreamReader(randomAccessStream.AsStreamForRead());
        var content = await reader.ReadToEndAsync();
        Console.WriteLine(content);
    }
}
