#include <stdio.h>
#include <stdlib.h>
#include <X11/extensions/Xrandr.h>

int
setGamma (double red, double green, double blue)
{
  Display *d;
  XRRScreenResources *xsr = NULL;
  XRRCrtcGamma *xcg;
  double gvalue;
  int gammaSize;

  if (!(d = XOpenDisplay (NULL))
      || !(xsr =
	   XRRGetScreenResourcesCurrent (d,
					 RootWindow (d, DefaultScreen (d)))))
    {
      printf ("XOpenDisplay or XRRGetScreenResourcesCurrent failed");
      return 1;
    }

  for (int i = 0; i < xsr->ncrtc; i++)
    {
      gammaSize = XRRGetCrtcGammaSize (d, xsr->crtcs[i]);
      if (!(xcg = XRRAllocGamma (gammaSize)))
	{
	  printf ("XRRAllocGamma failed");
	  return 1;
	}

      for (int j = 0; j < gammaSize; j++)
	{
	  gvalue = 65535.0 * j / gammaSize;
	  xcg->red[j] = gvalue * red;
	  xcg->green[j] = gvalue * green;
	  xcg->blue[j] = gvalue * blue;
	}

      XRRSetCrtcGamma (d, xsr->crtcs[i], xcg);
      XFree (xcg);
    }

  XFree (xsr), XCloseDisplay (d);

  return 0;
}

int
main (int argc, char *argv[])
{
  double rgb[3];
  int result;

  if (argc != 4)
    {
      printf ("Usage: xwhite RED GREEN BLUE\n"
	      "For example, set color temperture 3000K:\n"
	      "    xwhite 1.00000000 0.71976951 0.42860152");
      exit (1);
    }

  for (int i = 0; i < 3; i++)
    {
      rgb[i] = strtod (argv[i + 1], NULL);
      if (rgb[i] < 0 || rgb[i] > 1)
	{
	  printf ("R, G and B parameters must be between 0 and 1.\n");
	  exit (1);
	}
    }

  result = setGamma (rgb[0], rgb[1], rgb[2]);
  if (result != 0)
    {
      printf ("Set gamma failed.");
      exit (1);
    }

  return 0;
}
