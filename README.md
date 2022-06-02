# xwhite

Adjust X11 color via deviated white color, same as xrandr brightness adjustment instead of xrandr gamma correction in principle.

## Usage

```
// xwhite R G B
// R G B {0-1}, normalized, mapped to gamut, logrithmic
//       (sRGB primaries and gamma correction)
xwhite 1.00000000 0.71976951 0.42860152
// 3000K color temperture.
```

Reference for white color normalized RGB value regarding to color temperture: https://github.com/jonls/redshift/blob/master/README-colorramp: 
