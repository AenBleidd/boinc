# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="Property">
		<col key="yes" def="s72">Property</col>
		<col def="L0">Value</col>
		<col def="S255">ISComments</col>
		<row><td>ARPCOMMENTS</td><td>##IDS_SUMMARY_DESCRIPTION##</td><td/></row>
		<row><td>ARPHELPLINK</td><td>##COMPANY_URL##</td><td/></row>
		<row><td>ARPNOMODIFY</td><td>1</td><td/></row>
		<row><td>ARPNOREPAIR</td><td>1</td><td/></row>
		<row><td>ARPPRODUCTICON</td><td>ARPPRODUCTICON.exe</td><td/></row>
		<row><td>ARPREADME</td><td>##IDS_README_LOCATION##</td><td/></row>
		<row><td>ARPURLINFOABOUT</td><td>##COMPANY_URL##</td><td/></row>
		<row><td>ARPURLUPDATEINFO</td><td>##COMPANY_URL##</td><td/></row>
		<row><td>AgreeToLicense</td><td>No</td><td/></row>
		<row><td>BOINC_ADMINS_GROUPNAME</td><td/><td/></row>
		<row><td>BOINC_MASTER_PASSWORD</td><td/><td/></row>
		<row><td>BOINC_MASTER_USERNAME</td><td/><td/></row>
		<row><td>BOINC_PROJECTS_GROUPNAME</td><td/><td/></row>
		<row><td>BOINC_PROJECT_PASSWORD</td><td/><td/></row>
		<row><td>BOINC_PROJECT_USERNAME</td><td/><td/></row>
		<row><td>BOINC_USERS_GROUPNAME</td><td/><td/></row>
		<row><td>DATADIR</td><td/><td/></row>
		<row><td>DWUSINTERVAL</td><td>30</td><td/></row>
		<row><td>DWUSLINK</td><td>CE5CE738F9BC809F69AC80EFCE0B978F0EBC808FCEBC8038CE9B07DF4ECBB07FC92CF058A9AC</td><td/></row>
		<row><td>DefaultUIFont</td><td>Tahoma8</td><td/></row>
		<row><td>DialogCaption</td><td/><td/></row>
		<row><td>DiskPrompt</td><td>[1]</td><td/></row>
		<row><td>ENABLELAUNCHATLOGON</td><td>1</td><td/></row>
		<row><td>ENABLEPROTECTEDAPPLICATIONEXECUTION3</td><td/><td/></row>
		<row><td>ENABLESCREENSAVER</td><td>1</td><td/></row>
		<row><td>ENABLESTARTMENUITEMS</td><td>1</td><td/></row>
		<row><td>ENABLEUSEBYALLUSERS</td><td>1</td><td/></row>
		<row><td>ErrorDialog</td><td>SetupError</td><td/></row>
		<row><td>GROUPALIAS_ADMINISTRATORS</td><td/><td/></row>
		<row><td>GROUPALIAS_USERS</td><td/><td/></row>
		<row><td>INSTALLLEVEL</td><td>100</td><td/></row>
		<row><td>ISVROOT_PORT_NO</td><td>0</td><td/></row>
		<row><td>IS_PROGMSG_TEXTFILECHANGS_REPLACE</td><td>##IDS_PROGMSG_TEXTFILECHANGS_REPLACE##</td><td/></row>
		<row><td>IS_PROGMSG_XML_COSTING</td><td>##IDS_PROGMSG_XML_COSTING##</td><td/></row>
		<row><td>IS_PROGMSG_XML_CREATE_FILE</td><td>##IDS_PROGMSG_XML_CREATE_FILE##</td><td/></row>
		<row><td>IS_PROGMSG_XML_FILES</td><td>##IDS_PROGMSG_XML_FILES##</td><td/></row>
		<row><td>IS_PROGMSG_XML_REMOVE_FILE</td><td>##IDS_PROGMSG_XML_REMOVE_FILE##</td><td/></row>
		<row><td>IS_PROGMSG_XML_ROLLBACK_FILES</td><td>##IDS_PROGMSG_XML_ROLLBACK_FILES##</td><td/></row>
		<row><td>IS_PROGMSG_XML_UPDATE_FILE</td><td>##IDS_PROGMSG_XML_UPDATE_FILE##</td><td/></row>
		<row><td>InstallChoice</td><td>AR</td><td/></row>
		<row><td>LAUNCHPROGRAM</td><td>1</td><td/></row>
		<row><td>MSIRESTARTMANAGERCONTROL</td><td>Disable</td><td/></row>
		<row><td>Manufacturer</td><td>##COMPANY_NAME##</td><td/></row>
		<row><td>MsiHiddenProperties</td><td>BOINC_MASTER_PASSWORD;BOINC_PROJECT_PASSWORD</td><td/></row>
		<row><td>MsiLogging</td><td>voicewarmup</td><td/></row>
		<row><td>PIDTemplate</td><td>12345&lt;###-%%%%%%%&gt;@@@@@</td><td/></row>
		<row><td>PROGMSG_IIS_CREATEAPPPOOL</td><td>##IDS_PROGMSG_IIS_CREATEAPPPOOL##</td><td/></row>
		<row><td>PROGMSG_IIS_CREATEAPPPOOLS</td><td>##IDS_PROGMSG_IIS_CREATEAPPPOOLS##</td><td/></row>
		<row><td>PROGMSG_IIS_CREATEWEBSERVICEEXTENSION</td><td>##IDS_PROGMSG_IIS_CREATEWEBSERVICEEXTENSION##</td><td/></row>
		<row><td>PROGMSG_IIS_CREATEWEBSERVICEEXTENSIONS</td><td>##IDS_PROGMSG_IIS_CREATEWEBSERVICEEXTENSIONS##</td><td/></row>
		<row><td>PROGMSG_IIS_CREATEWEBSITE</td><td>##IDS_PROGMSG_IIS_CREATEWEBSITE##</td><td/></row>
		<row><td>PROGMSG_IIS_CREATEWEBSITES</td><td>##IDS_PROGMSG_IIS_CREATEWEBSITES##</td><td/></row>
		<row><td>PROGMSG_IIS_REMOVEAPPPOOL</td><td>##IDS_PROGMSG_IIS_REMOVEAPPPOOL##</td><td/></row>
		<row><td>PROGMSG_IIS_REMOVEAPPPOOLS</td><td>##IDS_PROGMSG_IIS_REMOVEAPPPOOLS##</td><td/></row>
		<row><td>PROGMSG_IIS_REMOVEWEBSERVICEEXTENSION</td><td>##IDS_PROGMSG_IIS_REMOVEWEBSERVICEEXTENSION##</td><td/></row>
		<row><td>PROGMSG_IIS_REMOVEWEBSERVICEEXTENSIONS</td><td>##IDS_PROGMSG_IIS_REMOVEWEBSERVICEEXTENSIONS##</td><td/></row>
		<row><td>PROGMSG_IIS_REMOVEWEBSITES</td><td>##IDS_PROGMSG_IIS_REMOVEWEBSITES##</td><td/></row>
		<row><td>PROGMSG_IIS_ROLLBACKAPPPOOLS</td><td>##IDS_PROGMSG_IIS_ROLLBACKAPPPOOLS##</td><td/></row>
		<row><td>PROGMSG_IIS_ROLLBACKWEBSERVICEEXTENSIONS</td><td>##IDS_PROGMSG_IIS_ROLLBACKWEBSERVICEEXTENSIONS##</td><td/></row>
		<row><td>PROGRAMFILETOLAUNCHATEND</td><td>[#boincmgr.exe]</td><td/></row>
		<row><td>ProductCode</td><td>{466F675C-6F57-4B63-AECF-29C62BDF58B0}</td><td/></row>
		<row><td>ProductID</td><td>none</td><td/></row>
		<row><td>ProductLanguage</td><td>1033</td><td/></row>
		<row><td>ProductName</td><td>BOINC</td><td/></row>
		<row><td>ProductVersion</td><td>8.1.0</td><td/></row>
		<row><td>ProgressType0</td><td>install</td><td/></row>
		<row><td>ProgressType1</td><td>Installing</td><td/></row>
		<row><td>ProgressType2</td><td>installed</td><td/></row>
		<row><td>ProgressType3</td><td>installs</td><td/></row>
		<row><td>RETURN_REBOOTREQUESTED</td><td>0</td><td/></row>
		<row><td>RETURN_VALIDATEINSTALL</td><td>0</td><td/></row>
		<row><td>RETURN_VERIFYINSTALLDIRECTORIES</td><td>0</td><td/></row>
		<row><td>RebootYesNo</td><td>Yes</td><td/></row>
		<row><td>ReinstallModeText</td><td>omus</td><td/></row>
		<row><td>RestartManagerOption</td><td>CloseRestart</td><td/></row>
		<row><td>SecureCustomProperties</td><td>ACTPROP_E913E54D_5080_42EC_A312_B21948BA1C02;INSTALLDIR;SUPPORTDIR;ENABLEPROTECTEDAPPLICATIONEXECUTION3;LAUNCHPROGRAM;ISACTIONPROP1;ISACTIONPROP2</td><td/></row>
		<row><td>UpgradeCode</td><td>{E913E54D-5080-42EC-A312-B21948BA1C02}</td><td/></row>
		<row><td>_BrowseDataProperty</td><td>0</td><td/></row>
		<row><td>_BrowseInstallProperty</td><td>0</td><td/></row>
		<row><td>_IsMaintenance</td><td>Install</td><td/></row>
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

