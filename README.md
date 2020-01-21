# CustomExpTable

CustomExpTable is a dll that you can compile to hook and change the EXP table function in MapleStory. This was made with v83 in mind to change it to [the older EXP/level up table from v62](http://wayback.hidden-street.net/exptable.php), but of course it can be customized to work with any version and apply any custom exp table. This will need to be changed in `ExpTableHook.h`.

## Installation

The dll has been compiled with use of [MaplePNP by Shavit](https://github.com/shavitush/MaplePnP) in mind. If you use the ijl15.dll and MaplePNP.dll from that project you can add this dll to your `plugins/` folder to enable the custom EXP table.