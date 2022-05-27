using ModManagerCommon;
using System.ComponentModel;

namespace SonicRModManager
{
	class SonicRLoaderInfo : LoaderInfo
	{
		public bool DebugConsole { get; set; }
		public bool DebugFile { get; set; }
		[DefaultValue(true)]
		public bool DebugCrashLog { get; set; }
		public bool Windowed { get; set; }
		[DefaultValue(640)]
		public int HorizontalResolution { get; set; } = 640;
		[DefaultValue(480)]
		public int VerticalResolution { get; set; } = 480;
		[DefaultValue(true)]
		public bool ForceAspectRatio { get; set; } = true;
		public bool WindowedFullscreen { get; set; }
		[DefaultValue(true)]
		public bool StretchFullscreen { get; set; } = true;
		public bool CustomWindowSize { get; set; }
		[DefaultValue(640)]
		public int WindowWidth { get; set; } = 640;
		[DefaultValue(480)]
		public int WindowHeight { get; set; } = 480;
		public bool MaintainWindowAspectRatio { get; set; }
	}
}
