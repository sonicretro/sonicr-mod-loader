using ModManagerCommon;
using System.ComponentModel;

namespace SonicRModManager
{
	class SonicRLoaderInfo : LoaderInfo
	{
		public bool DebugConsole { get; set; }
		public bool DebugFile { get; set; }
		public bool Windowed { get; set; }
		[DefaultValue(640)]
		public int HorizontalResolution { get; set; } = 640;
		[DefaultValue(480)]
		public int VerticalResolution { get; set; } = 480;
		[DefaultValue(true)]
		public bool ForceAspectRatio { get; set; } = true;
	}
}
