# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="CustomAction">
		<col key="yes" def="s72">Action</col>
		<col def="i2">Type</col>
		<col def="S64">Source</col>
		<col def="S0">Target</col>
		<col def="I4">ExtendedType</col>
		<col def="S255">ISComments</col>
		<row><td>CAAnnounceUpgrade</td><td>1</td><td>NewBinary6</td><td>AnnounceUpgrade</td><td/><td/></row>
		<row><td>CACleanupOldBinaries</td><td>1</td><td>NewBinary6</td><td>CleanupOldBinaries</td><td/><td/></row>
		<row><td>CACreateAcctMgrLoginFile</td><td>1</td><td>NewBinary6</td><td>CreateAcctMgrLoginFile</td><td/><td/></row>
		<row><td>CACreateBOINCAccounts</td><td>1</td><td>NewBinary6</td><td>CreateBOINCAccounts</td><td/><td/></row>
		<row><td>CACreateBOINCGroups</td><td>1</td><td>NewBinary6</td><td>CreateBOINCGroups</td><td/><td/></row>
		<row><td>CACreateClientAuthFile</td><td>1</td><td>NewBinary6</td><td>CreateClientAuthFile</td><td/><td/></row>
		<row><td>CACreateProjectInitFile</td><td>1</td><td>NewBinary6</td><td>CreateProjectInitFile</td><td/><td/></row>
		<row><td>CADeleteBOINCAccounts</td><td>65</td><td>NewBinary6</td><td>DeleteBOINCAccounts</td><td/><td/></row>
		<row><td>CADeleteBOINCGroups</td><td>1</td><td>NewBinary6</td><td>DeleteBOINCGroups</td><td/><td/></row>
		<row><td>CADisableProtectedApplicationExecution</td><td>51</td><td>ENABLEPROTECTEDAPPLICATIONEXECUTION3</td><td/><td/><td/></row>
		<row><td>CADisableUseByAllUsers</td><td>51</td><td>ENABLEUSEBYALLUSERS</td><td/><td/><td/></row>
		<row><td>CAGetAdministratorsGroupName</td><td>1</td><td>NewBinary6</td><td>GetAdministratorsGroupName</td><td/><td/></row>
		<row><td>CAGetUsersGroupName</td><td>1</td><td>NewBinary6</td><td>GetUsersGroupName</td><td/><td/></row>
		<row><td>CAGrantBOINCAdminsRights</td><td>1</td><td>NewBinary6</td><td>GrantBOINCAdminsRights</td><td/><td/></row>
		<row><td>CAGrantBOINCAdminsVirtualBoxRights</td><td>1</td><td>NewBinary6</td><td>GrantBOINCAdminsVirtualBoxRights</td><td/><td/></row>
		<row><td>CAGrantBOINCMasterRights</td><td>1</td><td>NewBinary6</td><td>GrantBOINCMasterRights</td><td/><td/></row>
		<row><td>CAGrantBOINCProjectRights</td><td>1</td><td>NewBinary6</td><td>GrantBOINCProjectRights</td><td/><td/></row>
		<row><td>CAGrantBOINCProjectsRights</td><td>1</td><td>NewBinary6</td><td>GrantBOINCProjectsRights</td><td/><td/></row>
		<row><td>CAGrantBOINCProjectsVirtualBoxRights</td><td>1</td><td>NewBinary6</td><td>GrantBOINCProjectsVirtualBoxRights</td><td/><td/></row>
		<row><td>CAGrantBOINCUsersRights</td><td>1</td><td>NewBinary6</td><td>GrantBOINCUsersRights</td><td/><td/></row>
		<row><td>CALaunchBOINCManager</td><td>65</td><td>NewBinary6</td><td>LaunchBOINCManager</td><td/><td/></row>
		<row><td>CALaunchBOINCTray</td><td>65</td><td>NewBinary6</td><td>LaunchBOINCTray</td><td/><td/></row>
		<row><td>CARestoreExecutionState</td><td>1</td><td>NewBinary6</td><td>RestoreExecutionState</td><td/><td/></row>
		<row><td>CARestorePermissionBOINCData</td><td>1</td><td>NewBinary6</td><td>RestorePermissionBOINCData</td><td/><td/></row>
		<row><td>CARestoreSetupState</td><td>1</td><td>NewBinary6</td><td>RestoreSetupState</td><td/><td/></row>
		<row><td>CARevokeBOINCAdminsRights</td><td>1</td><td>NewBinary6</td><td>RevokeBOINCAdminsRights</td><td/><td/></row>
		<row><td>CARevokeBOINCMasterRights</td><td>1</td><td>NewBinary6</td><td>RevokeBOINCMasterRights</td><td/><td/></row>
		<row><td>CARevokeBOINCProjectRights</td><td>1</td><td>NewBinary6</td><td>RevokeBOINCProjectRights</td><td/><td/></row>
		<row><td>CARevokeBOINCProjectsRights</td><td>1</td><td>NewBinary6</td><td>RevokeBOINCProjectsRights</td><td/><td/></row>
		<row><td>CARevokeBOINCUsersRights</td><td>1</td><td>NewBinary6</td><td>RevokeBOINCUsersRights</td><td/><td/></row>
		<row><td>CASaveExecutionState</td><td>1</td><td>NewBinary6</td><td>SaveExecutionState</td><td/><td/></row>
		<row><td>CASaveSetupState</td><td>1</td><td>NewBinary6</td><td>SaveSetupState</td><td/><td/></row>
		<row><td>CASetBOINCDataProjects</td><td>35</td><td>PROJECTS</td><td>[DATADIR]projects</td><td/><td/></row>
		<row><td>CASetBOINCDataSlots</td><td>35</td><td>SLOTS</td><td>[DATADIR]slots</td><td/><td/></row>
		<row><td>CASetPermissionBOINC</td><td>1</td><td>NewBinary6</td><td>SetPermissionBOINC</td><td/><td/></row>
		<row><td>CASetPermissionBOINCData</td><td>1</td><td>NewBinary6</td><td>SetPermissionBOINCData</td><td/><td/></row>
		<row><td>CASetPermissionBOINCDataProjects</td><td>1</td><td>NewBinary6</td><td>SetPermissionBOINCDataProjects</td><td/><td/></row>
		<row><td>CASetPermissionBOINCDataSlots</td><td>1</td><td>NewBinary6</td><td>SetPermissionBOINCDataSlots</td><td/><td/></row>
		<row><td>CAShutdownBOINC</td><td>1</td><td>NewBinary6</td><td>ShutdownBOINC</td><td/><td/></row>
		<row><td>CAShutdownBOINCManager</td><td>1</td><td>NewBinary6</td><td>ShutdownBOINCManager</td><td/><td/></row>
		<row><td>CAShutdownBOINCScreensaver</td><td>1</td><td>NewBinary6</td><td>ShutdownBOINCScreensaver</td><td/><td/></row>
		<row><td>CAValidateInstall</td><td>1</td><td>NewBinary6</td><td>ValidateInstall</td><td/><td/></row>
		<row><td>CAValidateRebootRequest</td><td>1</td><td>NewBinary6</td><td>ValidateRebootRequest</td><td/><td/></row>
		<row><td>CAValidateSetupType</td><td>1</td><td>NewBinary6</td><td>ValidateSetupType</td><td/><td/></row>
		<row><td>CAVerifyInstallDirectories</td><td>1</td><td>NewBinary6</td><td>VerifyInstallDirectories</td><td/><td/></row>
		<row><td>ISPreventDowngrade</td><td>19</td><td/><td>[IS_PREVENT_DOWNGRADE_EXIT]</td><td/><td/></row>
		<row><td>ISPrint</td><td>1</td><td>SetAllUsers.dll</td><td>PrintScrollableText</td><td/><td>Prints the contents of a ScrollableText control on a dialog.</td></row>
		<row><td>ISSetAllUsers</td><td>257</td><td>SetAllUsers.dll</td><td>SetAllUsers</td><td/><td/></row>
		<row><td>ISSetupFilesCleanup</td><td>257</td><td>ISSetupFilesHelper</td><td>SFCleanupEx</td><td/><td/></row>
		<row><td>ISSetupFilesExtract</td><td>257</td><td>ISSetupFilesHelper</td><td>SFStartupEx</td><td/><td/></row>
		<row><td>LaunchBOINCManagerXP</td><td>210</td><td>boincmgr.exe</td><td/><td/><td/></row>
		<row><td>LaunchBOINCTrayXP</td><td>210</td><td>boinctray.exe</td><td/><td/><td/></row>
		<row><td>SetARPINSTALLLOCATION</td><td>51</td><td>ARPINSTALLLOCATION</td><td>[INSTALLDIR]</td><td/><td/></row>
		<row><td>SetARPReadme</td><td>51</td><td>ARPREADME</td><td>[#readme.txt]</td><td/><td/></row>
		<row><td>SetAllUsersProfileNT</td><td>51</td><td>ALLUSERSPROFILE</td><td>[%SystemRoot]\Profiles\All Users</td><td/><td/></row>
		<row><td>setAllUsersProfile2K</td><td>51</td><td>ALLUSERSPROFILE</td><td>[%ALLUSERSPROFILE]</td><td/><td/></row>
		<row><td>setUserProfileNT</td><td>51</td><td>USERPROFILE</td><td>[%USERPROFILE]</td><td/><td/></row>
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

