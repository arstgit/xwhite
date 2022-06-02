#include <stdio.h>
#include <stdlib.h>
#include <X11/extensions/Xrandr.h>

void
setGamma (double red, double green, double blue)
{
  Display *d;
  XRRScreenResources *xsr = NULL;
  XRRCrtcGamma *xcg;
  double tmp;
  int gammaSize;

  if (!(d = XOpenDisplay (NULL))
      || !(xsr =
	   XRRGetScreenResourcesCurrent (d,
					 RootWindow (d, DefaultScreen (d)))))
    {
      printf ("XOpenDisplay or XRRGetScreenResourcesCurrent failed");
      return;
    }

  for (int i = 0; i < xsr->ncrtc; i++)
    {
      gammaSize = XRRGetCrtcGammaSize (d, xsr->crtcs[i]);
      if (!(xcg = XRRAllocGamma (gammaSize)))
	{
	  printf ("XRRAllocGamma failed");
	  return;
	}
      for (int j = 0; j < gammaSize; j++)
	{
	  tmp = 65535.0 * j / gammaSize;
	  xcg->red[j] = tmp * red;
	  xcg->green[j] = tmp * green;
	  xcg->blue[j] = tmp * blue;
	}
      XRRSetCrtcGamma (d, xsr->crtcs[i], xcg);
      XFree (xcg);
    }
  XFree (xsr), XCloseDisplay (d);
}

int
main (int argc, char *argv[])
{
  if (argc != 4)
    {
      printf ("Usage: xwhite RED GREEN BLUE\n"
	      "For example, set color temperture 3000K:\n"
	      "    xwhite 1.00000000 0.71976951 0.42860152");
      exit (1);
    }

  double red, green, blue;
  red = strtod (argv[1], NULL);
  green = strtod (argv[2], NULL);
  blue = strtod (argv[3], NULL);

  setGamma (red, green, blue);

  return 0;
}
