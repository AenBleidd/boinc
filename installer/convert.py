# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="RemoveFile">
		<col key="yes" def="s72">FileKey</col>
		<col def="s72">Component_</col>
		<col def="L255">FileName</col>
		<col def="s72">DirProperty</col>
		<col def="i2">InstallMode</col>
		<row><td>NewShortcut1</td><td>_BOINCManager</td><td/><td>BOINCLOCATIONTRAY</td><td>2</td></row>
		<row><td>NewShortcut2</td><td>_BOINCTray</td><td/><td>BOINCLOCATIONTRAY</td><td>2</td></row>
		<row><td>NewShortcut3</td><td>_BOINCManager</td><td/><td>BOINCLOCATIONMANAGER</td><td>2</td></row>
		<row><td>NewShortcut4</td><td>_BOINCManagerStartMenu</td><td/><td>newfolder1</td><td>2</td></row>
		<row><td>_BOINCTray</td><td>_BOINCTray</td><td/><td>BOINCLOCATIONTRAY</td><td>2</td></row>
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

