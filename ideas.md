## sysgrep

A simple tool to run _grep-like_ functionality against all readable files in a
system. Goals: manage threading for speed concerns, manage non-files, expose
attribute filtering for search.

Most simple functional version: grep everything in bash, use jobs, ignore
errors, always use _realpath_.
