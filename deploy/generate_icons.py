import warnings
import os
import PIL
import sys
from PIL import Image, ImageOps

# Define structs

class IconJob:
	def __init__(self, source, sourceMask, keepAlpha, targetBase, icons):
		self.source = source
		self.sourceMask = sourceMask
		self.keepAlpha = keepAlpha
		self.targetBase = targetBase
		self.icons = icons

class IconOut:
	def __init__(self, dest, size=0, rotation=0, bitdepth=32):
		self.dest = dest
		if (size and isinstance(size, int)):
			self.size = (size,size)
		else:
			self.size = size
		self.rotation = rotation
		self.bitdepth = bitdepth

class IconOut_NotSquare:
	def __init__(self, dest, width=0, height=0, rotation=0, bitdepth=32):
		self.dest = dest
		if (width and isinstance(width, int) and height and isinstance(height, int)):
			self.size = (width,height)
		else:
			self.size = width
		self.rotation = rotation
		self.bitdepth = bitdepth


# Define variables
master_icon_path = "master_icon.png"
master_splash = None
master_icon_fg_path = None
master_icon_bg_path = None
for_platforms = {
	# "win32": "../"
	"osx": "../src/xcode/Polyhedron.xcassets/AppIcon.appiconset",
	# "linux": 
	# "android": "../?",
	# "ios": "../?"
}

imagesToCreate = []

if "win32" in for_platforms:
	imagesToCreate.append(
		IconJob(source=master_icon_path, sourceMask="", keepAlpha=True, targetBase=for_platforms["win32"],
			icons=[
				IconOut("game.ico"),
			]
		)
	)

if "ios" in for_platforms:
	imagesToCreate.append(
		IconJob(source=master_icon_path, sourceMask="", keepAlpha=False, targetBase=for_platforms["ios"],
			icons=[
				IconOut("icon_29.png", 29),
				IconOut("icon_29-1.png", 29),
				IconOut("icon_40.png", 40),
				IconOut("icon_50.png", 50),
				IconOut("icon_57.png", 57),
				IconOut("icon_58.png", 58),
				IconOut("icon_58-1.png", 58),
				IconOut("icon_72.png", 72),
				IconOut("icon_76.png", 76),
				IconOut("icon_80.png", 80),
				IconOut("icon_80-2.png", 80),
				IconOut("icon_87.png", 87),
				IconOut("icon_100.png", 100),
				IconOut("icon_114.png", 114),
				IconOut("icon_120.png", 120),
				IconOut("icon_120-1.png", 120),
				IconOut("icon_144.png", 144),
				IconOut("icon_152.png", 152),
				IconOut("icon_167.png", 167),
				IconOut("icon_180.png", 180),
				IconOut("icon_1024.png", 1024),
			]
		)
	)

if "android" in for_platforms and master_splash:
	imagesToCreate.append(
		IconJob(source=master_splash, sourceMask="", keepAlpha=True, targetBase=for_platforms["android"],
			icons=[
				IconOut("drawable-ldpi/splash_logo.png", (256, 200)),
				IconOut("drawable-mdpi/splash_logo.png", (342, 266)),
				IconOut("drawable-hdpi/splash_logo.png", (512, 400)),
				IconOut("drawable-xhdpi/splash_logo.png", (684, 532)),
				IconOut("drawable-xxhdpi/splash_logo.png", (1026, 798)),
				IconOut("drawable-xxxhdpi/splash_logo.png", (1368, 1064)),
			]
		)
	)

	if master_icon_fg_path and master_icon_bg_path:
		imagesToCreate.append(
			IconJob(source=master_icon_fg_path, sourceMask="", keepAlpha=True, targetBase=for_platforms["android"],
				icons=[
					IconOut("mipmap-ldpi/icon_fg.png", 81),
					IconOut("mipmap-mdpi/icon_fg.png", 108),
					IconOut("mipmap-hdpi/icon_fg.png", 162),
					IconOut("mipmap-xhdpi/icon_fg.png", 216),
					IconOut("mipmap-xxhdpi/icon_fg.png", 324),
					IconOut("mipmap-xxxhdpi/icon_fg.png", 432),
				]
			)
		)

		imagesToCreate.append(
			IconJob(source=master_icon_bg_path, sourceMask="", keepAlpha=False, targetBase=for_platforms["android"],
				icons=[
					IconOut("mipmap-ldpi/icon_bg.png", 81),
					IconOut("mipmap-mdpi/icon_bg.png", 108),
					IconOut("mipmap-hdpi/icon_bg.png", 162),
					IconOut("mipmap-xhdpi/icon_bg.png", 216),
					IconOut("mipmap-xxhdpi/icon_bg.png", 324),
					IconOut("mipmap-xxxhdpi/icon_bg.png", 432),
				]
			)
		)
	else:
		imagesToCreate.append(
			IconJob(source=master_icon_path, sourceMask="", keepAlpha=True, targetBase=for_platforms["android"],
				icons=[
					IconOut("mipmap-ldpi/icon.png", 36),
					IconOut("mipmap-mdpi/icon.png", 48),
					IconOut("mipmap-hdpi/icon.png", 72),
					IconOut("mipmap-xhdpi/icon.png", 96),
					IconOut("mipmap-xxhdpi/icon.png", 144),
					IconOut("mipmap-xxxhdpi/icon.png", 192),
				]
			)
		)

if "osx" in for_platforms:
	imagesToCreate.append(
		IconJob(source=master_icon_path, sourceMask="", keepAlpha=True, targetBase=for_platforms["osx"],
			icons=[
				IconOut("polyhedron_16_1.png", 16),
				IconOut("polyhedron_16_2.png", 32),
				IconOut("polyhedron_32_1.png", 32),
				IconOut("polyhedron_32_2.png", 64),
				IconOut("polyhedron_128_1.png", 128),
				IconOut("polyhedron_128_2.png", 256),
				IconOut("polyhedron_256_1.png", 256),
				IconOut("polyhedron_256_2.png", 512),
				IconOut("polyhedron_512_1.png", 512),
				IconOut("polyhedron_512_2.png", 1024),
			]
		)
	)

def ensure_dir(f):
	if (f):
		d = os.path.dirname(f)
		if not os.path.exists(d):
			os.makedirs(d)

# Process all icons needed
for i,job in enumerate(imagesToCreate):
	if (not job.source):
		sys.exit("This job has no source: [" + str(i) + "]. Exiting.")

	if (not job.icons):
		warnings.warn("This job has no list of output icons: [" + str(i) + "].")
		continue

	if (not job.targetBase):
		job.targetBase = ""

	img = None
	print("Image job ", job.source)
	try:
		img = Image.open(job.source)

		if job.sourceMask and not job.sourceMask == "":
			if job.keepAlpha:
				img_mask = Image.open(job.sourceMask)
				if img_mask:
					tmpImg = Image.new("RGBA", img.size, (255, 255, 255, 255))
					tmpImg.paste(img)

					tmpMask = Image.new("L", tmpImg.size, (255))
					tmpMask.paste(img_mask)
					print("Got alpha ", job.sourceMask)
					alpha = tmpMask.split()[0]
					tmpImg.putalpha(alpha)

					img = tmpImg
			else:
				if len(img.getbands()) == 4:
					tmpImg = Image.new("RGB", img.size, (255, 255, 255))
					tmpImg.paste(img, mask=img.split()[3]) # 3 is the alpha channel
					img = tmpImg

		print("Success ", job.source)
	except IOError:
		print("Could not open image \"" + job.source + "\"")

	for _,icon in enumerate(job.icons):

		fileName = os.path.join(job.targetBase, icon.dest)
		print("Outputting \"" + fileName + "\"")

		outIcon = img
		if (icon.size):
			cropSize = icon.size
			if (icon.rotation):
				cropSize = (icon.size[1], icon.size[0])
			tmpIcon = ImageOps.fit(img, cropSize, method=Image.ANTIALIAS, centering=(0.5, 0.5))
			if (icon.rotation):
				outIcon = tmpIcon.transpose(PIL.Image.ROTATE_90)
			else:
				outIcon = tmpIcon

		ensure_dir(job.targetBase)
		try:
			ensure_dir(fileName)
			outIcon.save(fileName, optimize=True, quality=90, progressive=True)
		except IOError:
			print("Could not save image \"" + fileName + "\"")
