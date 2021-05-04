# table-viewer
Win32 program for viewing tables with GDI used as a rendeder
### Usage:
Pass the file name as a commandline parameter to open the file, 
otherwise the program will try to open the "table.txt" file in its folder.
Table width is scaled to the window size
Use mouse wheel to scroll through the table
### Table format:
- first line must contain rows and columns numbers delimited by at least one whitespace character
- seсond and consequent lines represent table cells - one cell per line
- add a line break to insert an empty cell
