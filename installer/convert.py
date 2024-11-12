# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="LaunchCondition">
		<col key="yes" def="s255">Condition</col>
		<col def="l255">Description</col>
		<row><td>((Not Version9X=400) And (Not Version9X=410) And (Not Version9X=490) And (Not VersionNT=400)) And (VersionNT&gt;500)</td><td>##ID_STRING39##</td></row>
		<row><td>AdminUser</td><td>##IDPROP_EXPRESS_LAUNCH_CONDITION_ADMIN##</td></row>
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

