# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="Upgrade">
		<col key="yes" def="s38">UpgradeCode</col>
		<col key="yes" def="S20">VersionMin</col>
		<col key="yes" def="S20">VersionMax</col>
		<col key="yes" def="S255">Language</col>
		<col key="yes" def="i4">Attributes</col>
		<col def="S255">Remove</col>
		<col def="s72">ActionProperty</col>
		<col def="S72">ISDisplayName</col>
		<row><td>{76DD37FC-EE51-408D-9FB5-3D59FC8ED22A}</td><td>0000.0000.0000</td><td>9999.9999.9999</td><td></td><td>769</td><td/><td>ISACTIONPROP2</td><td>World Community Grid Upgrade (7.14.2)</td></row>
		<row><td>{862B80F6-835D-4F72-8C4F-EE68ED34C6F8}</td><td>0000.0000.0000</td><td>9999.9999.9999</td><td></td><td>769</td><td/><td>ISACTIONPROP1</td><td>World Community Grid Upgrade</td></row>
		<row><td>{E913E54D-5080-42EC-A312-B21948BA1C02}</td><td>0000.0000.0000</td><td>9999.9999.9999</td><td></td><td>769</td><td/><td>ACTPROP_E913E54D_5080_42EC_A312_B21948BA1C02</td><td>General Upgrade</td></row>
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

