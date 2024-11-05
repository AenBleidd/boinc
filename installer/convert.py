# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="RadioButton">
		<col key="yes" def="s72">Property</col>
		<col key="yes" def="i2">Order</col>
		<col def="s64">Value</col>
		<col def="i2">X</col>
		<col def="i2">Y</col>
		<col def="i2">Width</col>
		<col def="i2">Height</col>
		<col def="L64">Text</col>
		<col def="L50">Help</col>
		<col def="I4">ISControlId</col>
		<row><td>AgreeToLicense</td><td>1</td><td>No</td><td>0</td><td>15</td><td>291</td><td>15</td><td>##IDS__AgreeToLicense_0##</td><td/><td/></row>
		<row><td>AgreeToLicense</td><td>2</td><td>Yes</td><td>0</td><td>0</td><td>291</td><td>15</td><td>##IDS__AgreeToLicense_1##</td><td/><td/></row>
		<row><td>RestartManagerOption</td><td>1</td><td>CloseRestart</td><td>6</td><td>9</td><td>331</td><td>14</td><td>##IDS__IsMsiRMFilesInUse_CloseRestart##</td><td/><td/></row>
		<row><td>RestartManagerOption</td><td>2</td><td>Reboot</td><td>6</td><td>21</td><td>331</td><td>14</td><td>##IDS__IsMsiRMFilesInUse_RebootAfter##</td><td/><td/></row>
		<row><td>SETUPTYPE</td><td>1</td><td>Single</td><td>0</td><td>0</td><td>270</td><td>15</td><td>##IDS__IsSetupTypeDlg_Single##</td><td/><td>0</td></row>
		<row><td>SETUPTYPE</td><td>2</td><td>Shared</td><td>0</td><td>38</td><td>270</td><td>15</td><td>##IDS__IsSetupTypeDlg_Shared##</td><td/><td>0</td></row>
		<row><td>SETUPTYPE</td><td>3</td><td>Service</td><td>0</td><td>75</td><td>270</td><td>15</td><td>##IDS__IsSetupTypeDlg_Service##</td><td/><td>0</td></row>
		<row><td>_IsMaintenance</td><td>2</td><td>Reinstall</td><td>0</td><td>0</td><td>290</td><td>14</td><td>##IDS__IsMaintenanceDlg_Repair##</td><td/><td>0</td></row>
		<row><td>_IsMaintenance</td><td>3</td><td>Remove</td><td>0</td><td>60</td><td>290</td><td>14</td><td>##IDS__IsMaintenanceDlg_Remove##</td><td/><td>0</td></row>
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
print(json_data_new)
# Write the JSON data to a file
with open('installer/at.json', 'w') as f:
    f.write(json_data_new)

