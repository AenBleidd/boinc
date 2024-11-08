# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="FeatureComponents">
		<col key="yes" def="s38">Feature_</col>
		<col key="yes" def="s72">Component_</col>
		<row><td>BOINC</td><td>BOINCServiceConfig</td></row>
		<row><td>BOINC</td><td>_BOINC</td></row>
		<row><td>BOINC</td><td>_BOINCCMD</td></row>
		<row><td>BOINC</td><td>_BOINCData</td></row>
		<row><td>BOINC</td><td>_BOINCDataProjects</td></row>
		<row><td>BOINC</td><td>_BOINCDataSlots</td></row>
		<row><td>BOINC</td><td>_BOINCDepends</td></row>
		<row><td>BOINC</td><td>_BOINCSvcCtrl</td></row>
		<row><td>BOINC</td><td>_BOINCTray</td></row>
		<row><td>BOINC</td><td>_BOINCTrayStartup</td></row>
		<row><td>BOINCManager</td><td>_BOINCManager</td></row>
		<row><td>BOINCManager</td><td>_BOINCManagerSkin</td></row>
		<row><td>BOINCManager</td><td>_BOINCManagerStartMenu</td></row>
		<row><td>BOINCManagerGlobalization</td><td>_BOINCManagerGlobalization</td></row>
		<row><td>BOINCManagerStartup</td><td>_BOINCManagerStartup</td></row>
		<row><td>BOINCManagerStartup</td><td>_BOINCManagerStartupAll</td></row>
		<row><td>BOINCScreensaver</td><td>_BOINCScreensaver</td></row>
		<row><td>BOINCScreensaver</td><td>_Screensaver</td></row>
		<row><td>BOINCScreensaver</td><td>_ScreensaverEnable9x</td></row>
		<row><td>BOINCScreensaver</td><td>_ScreensaverEnableNT</td></row>
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

