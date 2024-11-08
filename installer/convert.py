# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="Component">
		<col key="yes" def="s72">Component</col>
		<col def="S38">ComponentId</col>
		<col def="s72">Directory_</col>
		<col def="i2">Attributes</col>
		<col def="S255">Condition</col>
		<col def="S72">KeyPath</col>
		<col def="I4">ISAttributes</col>
		<col def="S255">ISComments</col>
		<col def="S255">ISScanAtBuildFile</col>
		<col def="S255">ISRegFileToMergeAtBuild</col>
		<col def="S0">ISDotNetInstallerArgsInstall</col>
		<col def="S0">ISDotNetInstallerArgsCommit</col>
		<col def="S0">ISDotNetInstallerArgsUninstall</col>
		<col def="S0">ISDotNetInstallerArgsRollback</col>
		<row><td>BOINCServiceConfig</td><td>{3BD51E4E-504D-43C2-AD8A-2FAD36A43488}</td><td>INSTALLDIR</td><td>256</td><td>VersionNT AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1</td><td>boinc.exe1</td><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINC</td><td>{B2649E11-6320-4710-B5C8-1922588446E9}</td><td>INSTALLDIR</td><td>256</td><td/><td>boinc.exe</td><td>145</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCCMD</td><td>{02757F30-2A56-4AB4-99DC-92F0AA5A84A5}</td><td>INSTALLDIR</td><td>256</td><td/><td>boinccmd.exe</td><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCData</td><td>{4E793828-A468-4366-892F-FC2F36EC99D9}</td><td>DATADIR</td><td>272</td><td/><td/><td>145</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCDataProjects</td><td>{9C720438-35E8-4377-A105-AF3675664094}</td><td>PROJECTS</td><td>272</td><td/><td/><td>145</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCDataSlots</td><td>{C9FE7A6E-2470-4666-949B-4DB2BB936E5F}</td><td>SLOTS</td><td>272</td><td/><td/><td>145</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCDepends</td><td>{69AF1C45-9D67-4F33-B97B-5DA096D77908}</td><td>INSTALLDIR</td><td>256</td><td/><td/><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCManager</td><td>{7EBB5E76-86BA-4EBA-98AA-DD908C215D72}</td><td>INSTALLDIR</td><td>256</td><td/><td>boincmgr.exe</td><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCManagerGlobalization</td><td>{F92B6595-2E79-45F0-BF41-4EDB52645FFC}</td><td>LOCALE</td><td>256</td><td/><td/><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCManagerSkin</td><td>{73A92885-CE76-42CE-916B-1B52DAADD11C}</td><td>DEFAULT</td><td>256</td><td/><td/><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCManagerStartMenu</td><td>{B2F97C0C-F33E-453D-B304-228A1686C6DF}</td><td>INSTALLDIR</td><td>256</td><td>ENABLESTARTMENUITEMS = 1</td><td/><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCManagerStartup</td><td>{16BC187E-DE09-453E-AD35-0C6BEF32BA73}</td><td>INSTALLDIR</td><td>256</td><td>ENABLEUSEBYALLUSERS &lt;&gt; 1</td><td/><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCManagerStartupAll</td><td>{175B1B4B-D4D7-4D21-968A-8EDF6F8C4BE3}</td><td>INSTALLDIR</td><td>256</td><td>ENABLEUSEBYALLUSERS = 1</td><td/><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCScreensaver</td><td>{DE9384B0-EA5F-43E3-90A9-41097728DF22}</td><td>INSTALLDIR</td><td>264</td><td/><td>boincscr.exe</td><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCSvcCtrl</td><td>{B307063C-7B0A-458A-A707-2E23B6545E9B}</td><td>INSTALLDIR</td><td>256</td><td/><td>boincsvcctrl.exe</td><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCTray</td><td>{F21E62FE-3BA7-401B-BDBA-D96259DCBD3B}</td><td>INSTALLDIR</td><td>256</td><td>VersionNT</td><td>boinctray.exe</td><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_BOINCTrayStartup</td><td>{BEB2BDC7-6AB8-4EA0-B9E8-323B07532AFF}</td><td>INSTALLDIR</td><td>264</td><td/><td/><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_Screensaver</td><td>{B7ED8F6D-37AE-4F3A-A8C5-127DE44C483A}</td><td>WindowsFolder</td><td>256</td><td/><td>boinc.scr</td><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_ScreensaverEnable9x</td><td>{E3BA83A8-3650-4133-8720-D336D3FFD477}</td><td>INSTALLDIR</td><td>256</td><td>Version9X AND ENABLESCREENSAVER = 1</td><td/><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
		<row><td>_ScreensaverEnableNT</td><td>{2F8CEFC8-A589-4CF7-BEE4-F7149D08C712}</td><td>INSTALLDIR</td><td>256</td><td>VersionNT AND ENABLESCREENSAVER = 1</td><td/><td>17</td><td/><td/><td/><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td><td>/LogFile=</td></row>
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

