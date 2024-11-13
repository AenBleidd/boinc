# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="Registry">
		<col key="yes" def="s72">Registry</col>
		<col def="i2">Root</col>
		<col def="s255">Key</col>
		<col def="S255">Name</col>
		<col def="S0">Value</col>
		<col def="s72">Component_</col>
		<col def="I4">ISAttributes</col>
		<row><td>Registry1</td><td>1</td><td>Control Panel\Desktop</td><td>SCRNSAVE.EXE</td><td>boinc.scr</td><td>_ScreensaverEnableNT</td><td>0</td></row>
		<row><td>Registry2</td><td>1</td><td>Control Panel\Desktop</td><td>ScreenSaveActive</td><td>1</td><td>_ScreensaverEnableNT</td><td>0</td></row>
		<row><td>Registry3</td><td>1</td><td>SOFTWARE\Microsoft\Windows\CurrentVersion\Run</td><td>boincmgr</td><td>"[INSTALLDIR]boincmgr.exe" /a /s</td><td>_BOINCManagerStartup</td><td>0</td></row>
		<row><td>Registry30</td><td>2</td><td>SOFTWARE\Microsoft\Windows\CurrentVersion\Run</td><td>boinctray</td><td>"[INSTALLDIR]boinctray.exe"</td><td>_BOINCTrayStartup</td><td>0</td></row>
		<row><td>Registry4</td><td>1</td><td>Control Panel\Desktop</td><td>ScreenSaveTimeOut</td><td>300</td><td>_ScreensaverEnableNT</td><td>0</td></row>
		<row><td>Registry5</td><td>2</td><td>SOFTWARE\Microsoft\Windows\CurrentVersion\Run</td><td>boincmgr</td><td>"[INSTALLDIR]boincmgr.exe" /a /s</td><td>_BOINCManagerStartupAll</td><td>0</td></row>
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

