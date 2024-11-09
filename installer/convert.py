# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="File">
		<col key="yes" def="s72">File</col>
		<col def="s72">Component_</col>
		<col def="s255">FileName</col>
		<col def="i4">FileSize</col>
		<col def="S72">Version</col>
		<col def="S20">Language</col>
		<col def="I2">Attributes</col>
		<col def="i2">Sequence</col>
		<col def="S255">ISBuildSourcePath</col>
		<col def="I4">ISAttributes</col>
		<col def="S72">ISComponentSubFolder_</col>
		<row><td>all_projects_list.xml</td><td>_BOINCData</td><td>ALL_PR~1.XML|all_projects_list.xml</td><td>0</td><td/><td/><td>0</td><td>1</td><td>&lt;ISProjectFolder&gt;\redist\all_projects_list.xml</td><td>1</td><td/></row>
		<row><td>boinc.exe</td><td>_BOINC</td><td>boinc.exe</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_RELEASE_FILES&gt;\boinc.exe</td><td>1</td><td/></row>
		<row><td>boinc.exe1</td><td>BOINCServiceConfig</td><td>boinc.exe</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_RELEASE_FILES&gt;\boinc.exe</td><td>1</td><td/></row>
		<row><td>boinc.scr</td><td>_Screensaver</td><td>boinc.scr</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_RELEASE_FILES&gt;\boinc.scr</td><td>1</td><td/></row>
		<row><td>boinc_logo_black.jpg</td><td>_BOINCScreensaver</td><td>BOINC_~1.JPG|boinc_logo_black.jpg</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_LOGO_FILES&gt;\boinc_logo_black.jpg</td><td>1</td><td/></row>
		<row><td>boinccmd.exe</td><td>_BOINCCMD</td><td>boinccmd.exe</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_RELEASE_FILES&gt;\boinccmd.exe</td><td>1</td><td/></row>
		<row><td>boincmgr.exe</td><td>_BOINCManager</td><td>boincmgr.exe</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_RELEASE_FILES&gt;\boincmgr.exe</td><td>1</td><td/></row>
		<row><td>boincscr.exe</td><td>_BOINCScreensaver</td><td>boincscr.exe</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_RELEASE_FILES&gt;\boincscr.exe</td><td>1</td><td/></row>
		<row><td>boincsvcctrl.exe</td><td>_BOINCSvcCtrl</td><td>BOINCS~1.EXE|boincsvcctrl.exe</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_RELEASE_FILES&gt;\boincsvcctrl.exe</td><td>1</td><td/></row>
		<row><td>boinctray.exe</td><td>_BOINCTray</td><td>BOINCT~1.EXE|boinctray.exe</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_RELEASE_FILES&gt;\boinctray.exe</td><td>1</td><td/></row>
		<row><td>ca_bundle.crt</td><td>_BOINCDepends</td><td>CA-BUN~1.CRT|ca-bundle.crt</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_RELEASE_FILES&gt;\ca-bundle.crt</td><td>1</td><td/></row>
		<row><td>copying</td><td>_BOINCDepends</td><td>COPYING</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_BOINC_FILES&gt;\COPYING</td><td>1</td><td/></row>
		<row><td>copyright</td><td>_BOINCDepends</td><td>COPYRI~1|COPYRIGHT</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_BOINC_FILES&gt;\COPYRIGHT</td><td>1</td><td/></row>
		<row><td>liberationsans_regular.ttf</td><td>_BOINCScreensaver</td><td>LIBERA~1.TTF|LiberationSans-Regular.ttf</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;PATH_TO_BOINC_FILES&gt;\api\ttf\liberation-fonts-ttf-2.00.0\LiberationSans-Regular.ttf</td><td>1</td><td/></row>
		<row><td>placeholder.txt</td><td>_BOINCData</td><td>PLACEH~1.TXT|placeholder.txt</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;ISProjectFolder&gt;\redist\placeholder.txt</td><td>1</td><td/></row>
		<row><td>placeholder.txt1</td><td>_BOINCDataProjects</td><td>PLACEH~1.TXT|placeholder.txt</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;ISProjectFolder&gt;\redist\placeholder.txt</td><td>1</td><td/></row>
		<row><td>placeholder.txt2</td><td>_BOINCDataSlots</td><td>PLACEH~1.TXT|placeholder.txt</td><td>0</td><td/><td/><td/><td>1</td><td>&lt;ISProjectFolder&gt;\redist\placeholder.txt</td><td>1</td><td/></row>
	</table>
'''

# Parse the XML data
root = ET.fromstring(xml_data)

# Extract column names from <col> elements
columns = [col.text for col in root.findall('col')]

# Extract rows and convert to dictionary format
rows = []
for row in root.findall('row'):
    row_data = {}
    for col, cell in zip(columns, row.findall('td')):
        row_data[col] = cell.text
    rows.append(row_data)

# Convert to JSON
json_data = json.dumps(rows, indent=4)

# json_new = []
# for row in rows:
#     new_row = {
#         'Action': row['Action'],
#         'Condition': row['Condition'],
#         'Sequence': row['Sequence']
#     }
# # add the new row to the new json structure
#     json_new.append(new_row)

# Convert to JSON
json_data_new = json.dumps(rows, indent=4)
# print(json_data_new)
# Write the JSON data to a file
with open('installer/at.json', 'w') as f:
    f.write(json_data_new)

