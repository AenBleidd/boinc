# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="Feature">
		<col key="yes" def="s38">Feature</col>
		<col def="S38">Feature_Parent</col>
		<col def="L64">Title</col>
		<col def="L255">Description</col>
		<col def="I2">Display</col>
		<col def="i2">Level</col>
		<col def="S72">Directory_</col>
		<col def="i2">Attributes</col>
		<col def="S255">ISReleaseFlags</col>
		<col def="S255">ISComments</col>
		<col def="S255">ISFeatureCabName</col>
		<col def="S255">ISProFeatureName</col>
		<row><td>BOINC</td><td/><td>##IDS_FEATURE_BOINC_NAME##</td><td>##IDS_FEATURE_BOINC_DESCRIPTION##</td><td>3</td><td>1</td><td>INSTALLDIR</td><td>16</td><td/><td/><td/><td/></row>
		<row><td>BOINCManager</td><td>BOINC</td><td>##IDS_FEATURE_BOINC_MANAGER_NAME##</td><td>##IDS_FEATURE_BOINC_MANAGER_DESCRIPTION##</td><td>13</td><td>1</td><td>INSTALLDIR</td><td>2</td><td/><td/><td/><td/></row>
		<row><td>BOINCManagerGlobalization</td><td>BOINCManager</td><td>##IDS_FEATURE_BOINC_MANAGER_GLOBALIZATION_NAME##</td><td>##IDS_FEATURE_BOINC_MANAGER_GLOBALIZATION_DESCRIPTION##</td><td>1</td><td>1</td><td>INSTALLDIR</td><td>2</td><td/><td/><td/><td/></row>
		<row><td>BOINCManagerStartup</td><td>BOINCManager</td><td>***IS_STRING_NOT_DEFINED***</td><td/><td>7</td><td>1</td><td>INSTALLDIR</td><td>2</td><td/><td/><td/><td/></row>
		<row><td>BOINCScreensaver</td><td>BOINC</td><td>##IDS_FEATURE_BOINC_SCREENSAVER_NAME##</td><td>##IDS_FEATURE_BOINC_SCREENSAVER_DESCRIPTION##</td><td>15</td><td>1</td><td>INSTALLDIR</td><td>18</td><td/><td/><td/><td/></row>
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

