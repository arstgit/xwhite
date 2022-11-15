# xwhite

It is a command line tool for adjusting the colour balance of screen.  It is based on xrandr's gamma correction and brightness adjustment.  As such, it can only be used for X displays and not Wayland displays.  It is typically used for tuning the color balance and color temperature.  

It has a similar function as `redshift -P -g R:G:B -O temperature`, but `xwhite` is more flexible in that it does not keep the white color fixed, suitable for setting the white color to an arbitrary balanced color.

## Usage

```
// xwhite --output <output> --rgb <R>:<G>:<B>
// R G B {0-1}, normalized, mapped to gamut, logrithmic
//       (sRGB primaries and gamma correction)
xwhite --output LVDS-1 --rgb 1.00000000:0.71976951:0.42860152
// 3000K color temperture.
```

Reference for white color normalized RGB value regarding to color temperture: https://github.com/jonls/redshift/blob/master/README-colorramp.

## License

GPL-2.0-only license no later versions.
