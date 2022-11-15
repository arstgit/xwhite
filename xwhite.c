#include <X11/extensions/Xrandr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int setGamma(char *output_name, double red, double green, double blue) {
  Display *d;
  XRRScreenResources *xsr = NULL;
  XRRCrtcGamma *xcg;
  double gvalue;
  int gammaSize;
  int found = 0;

  if (!(d = XOpenDisplay(NULL)) || !(xsr = XRRGetScreenResourcesCurrent(
                                         d, RootWindow(d, DefaultScreen(d))))) {
    printf("XOpenDisplay or XRRGetScreenResourcesCurrent failed");
    return 1;
  }

  for (int o = 0; o < xsr->noutput; o++) {
    XRROutputInfo *output_info = XRRGetOutputInfo(d, xsr, xsr->outputs[o]);
    if (!output_info) {
      printf("could not get output 0x%lx information\n", xsr->outputs[o]);
      return 1;
    }

    RRCrtc crtc = output_info->crtc;

    if (!strcmp(output_name, output_info->name)) {
      found++;

      gammaSize = XRRGetCrtcGammaSize(d, crtc);
      if (!(xcg = XRRAllocGamma(gammaSize))) {
        printf("XRRAllocGamma failed");
        return 1;
      }

      for (int j = 0; j < gammaSize; j++) {
        gvalue = 65535.0 * j / gammaSize;
        xcg->red[j] = gvalue * red;
        xcg->green[j] = gvalue * green;
        xcg->blue[j] = gvalue * blue;
      }

      XRRSetCrtcGamma(d, crtc, xcg);
      XFree(xcg);
    }
    XFree(output_info);
  }

  if (found == 0) {
    printf("Output not found: %s.\n", output_name);
    return 1;
  }

  XFree(xsr), XCloseDisplay(d);

  return 0;
}

int main(int argc, char *argv[]) {
  double rgb[3];
  char *output_name;
  int result;

  if (argc < 5) {
    printf(
        "Usage: xwhite --output <crtc> --rgb <red>:<green>:<blue>\n"
        "For example, set color temperture 3000K on a monitor named LVDS-1:\n"
        "    xwhite --output LVDS-1 --rgb "
        "1.00000000:0.71976951:0.42860152\n");
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    if (!strcmp("--output", argv[i])) {
      if (++i >= argc) {
        printf("%s requires an argument\n", argv[i - 1]);
        exit(1);
      }
      output_name = argv[i];

      continue;
    }
    if (!strcmp("--rgb", argv[i])) {
      if (++i >= argc)
        printf("%s requires an argument\n", argv[i - 1]);
      if (sscanf(argv[i], "%lf:%lf:%lf", &rgb[0], &rgb[1], &rgb[2]) != 3) {
        printf("%s: invalid argument '%s'\n", argv[i - 1], argv[i]);
        exit(1);
      }
      if (rgb[i] < 0 || rgb[i] > 1) {
        printf("R, G and B parameters must be between 0 and 1.\n");
        exit(1);
      }
      continue;
    }

    printf("unrecognized option %s\n", argv[i]);
    exit(1);
  }

  result = setGamma(output_name, rgb[0], rgb[1], rgb[2]);
  if (result != 0) {
    printf("Set gamma failed.\n");
    exit(1);
  }

  return 0;
}
