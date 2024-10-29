# read XML document and convert it to a dictionary
import xml.etree.ElementTree as ET
import json

xml_data = r'''
	<table name="ControlCondition">
		<col key="yes" def="s72">Dialog_</col>
		<col key="yes" def="s50">Control_</col>
		<col key="yes" def="s50">Action</col>
		<col key="yes" def="s255">Condition</col>
		<row><td>InstallWelcome</td><td>Copyright</td><td>Hide</td><td>SHOWCOPYRIGHT="No"</td></row>
		<row><td>InstallWelcome</td><td>Copyright</td><td>Show</td><td>SHOWCOPYRIGHT="Yes"</td></row>
		<row><td>LicenseAgreement</td><td>Next</td><td>Disable</td><td>AgreeToLicense &lt;&gt; "Yes"</td></row>
		<row><td>LicenseAgreement</td><td>Next</td><td>Enable</td><td>AgreeToLicense = "Yes"</td></row>
		<row><td>ReadyToInstall</td><td>DlgTitle</td><td>Show</td><td>ProgressType0="Modify"</td></row>
		<row><td>ReadyToInstall</td><td>DlgTitle2</td><td>Show</td><td>ProgressType0="Repair"</td></row>
		<row><td>ReadyToInstall</td><td>DlgTitle3</td><td>Show</td><td>ProgressType0="install"</td></row>
		<row><td>SetupCompleteError</td><td>Back</td><td>Default</td><td>UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>Back</td><td>Disable</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>Back</td><td>Enable</td><td>UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>Cancel</td><td>Disable</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>Cancel</td><td>Enable</td><td>UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>Finish</td><td>Default</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>FinishText1</td><td>Hide</td><td>UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>FinishText1</td><td>Show</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>FinishText2</td><td>Hide</td><td>UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>FinishText2</td><td>Show</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>RestContText1</td><td>Hide</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>RestContText1</td><td>Show</td><td>UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>RestContText2</td><td>Hide</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupCompleteError</td><td>RestContText2</td><td>Show</td><td>UpdateStarted</td></row>
		<row><td>SetupCompleteSuccess</td><td>LaunchProgramCheck</td><td>Show</td><td>PROGRAMFILETOLAUNCHATEND &lt;&gt; "" And ACTION &lt;&gt; "ADMIN" And RETURN_VALIDATEINSTALL = "1" And RETURN_REBOOTREQUESTED = "0" And NOT Installed</td></row>
		<row><td>SetupCompleteSuccess</td><td>LaunchProgramText</td><td>Show</td><td>PROGRAMFILETOLAUNCHATEND &lt;&gt; "" And ACTION &lt;&gt; "ADMIN" And RETURN_VALIDATEINSTALL = "1" And RETURN_REBOOTREQUESTED = "0" And NOT Installed</td></row>
		<row><td>SetupCompleteSuccess</td><td>RebootText</td><td>Show</td><td>RETURN_REBOOTREQUESTED = "1"</td></row>
		<row><td>SetupCompleteSuccess</td><td>RepairText</td><td>Show</td><td>RETURN_VALIDATEINSTALL = "0" AND _IsMaintenance &lt;&gt; "Remove"</td></row>
		<row><td>SetupCompleteSuccess</td><td>TextLine2</td><td>Show</td><td>ProgressType2="installed" And ((ACTION&lt;&gt;"INSTALL") OR (NOT ISENABLEDWUSFINISHDIALOG) OR (ISENABLEDWUSFINISHDIALOG And Installed))</td></row>
		<row><td>SetupCompleteSuccess</td><td>TextLine3</td><td>Show</td><td>ProgressType2="uninstalled" And ((ACTION&lt;&gt;"INSTALL") OR (NOT ISENABLEDWUSFINISHDIALOG) OR (ISENABLEDWUSFINISHDIALOG And Installed))</td></row>
		<row><td>SetupCompleteSuccess</td><td>UpdateTextLine1</td><td>Show</td><td>ISENABLEDWUSFINISHDIALOG And NOT Installed And ACTION="INSTALL"</td></row>
		<row><td>SetupConfigAdvanced</td><td>CheckBox3</td><td>Disable</td><td>NOT VersionNT</td></row>
		<row><td>SetupConfigAdvanced</td><td>CheckBox4</td><td>Disable</td><td>NOT VersionNT</td></row>
		<row><td>SetupConfigAdvanced</td><td>Text5</td><td>Hide</td><td>VersionNT &gt;= 600</td></row>
		<row><td>SetupConfigAdvanced</td><td>Text5</td><td>Show</td><td>Version9X OR VersionNT &lt; 600</td></row>
		<row><td>SetupConfigAdvanced</td><td>Text6</td><td>Hide</td><td>Version9X OR VersionNT &lt; 600</td></row>
		<row><td>SetupConfigAdvanced</td><td>Text6</td><td>Show</td><td>VersionNT &gt;= 600</td></row>
		<row><td>SetupInterrupted</td><td>Back</td><td>Default</td><td>UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>Back</td><td>Disable</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>Back</td><td>Enable</td><td>UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>Cancel</td><td>Disable</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>Cancel</td><td>Enable</td><td>UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>Finish</td><td>Default</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>FinishText1</td><td>Hide</td><td>UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>FinishText1</td><td>Show</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>FinishText2</td><td>Hide</td><td>UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>FinishText2</td><td>Show</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>RestContText1</td><td>Hide</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>RestContText1</td><td>Show</td><td>UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>RestContText2</td><td>Hide</td><td>NOT UpdateStarted</td></row>
		<row><td>SetupInterrupted</td><td>RestContText2</td><td>Show</td><td>UpdateStarted</td></row>
		<row><td>SetupProgress</td><td>DlgDesc</td><td>Show</td><td>ProgressType2="installed"</td></row>
		<row><td>SetupProgress</td><td>DlgDesc2</td><td>Show</td><td>ProgressType2="uninstalled"</td></row>
		<row><td>SetupProgress</td><td>DlgText</td><td>Show</td><td>ProgressType3="installs"</td></row>
		<row><td>SetupProgress</td><td>DlgText2</td><td>Show</td><td>ProgressType3="uninstalls"</td></row>
		<row><td>SetupProgress</td><td>DlgTitle</td><td>Show</td><td>ProgressType1="Installing"</td></row>
		<row><td>SetupProgress</td><td>DlgTitle2</td><td>Show</td><td>ProgressType1="Uninstalling"</td></row>
		<row><td>SetupResume</td><td>PreselectedText</td><td>Hide</td><td>RESUME</td></row>
		<row><td>SetupResume</td><td>PreselectedText</td><td>Show</td><td>NOT RESUME</td></row>
		<row><td>SetupResume</td><td>ResumeText</td><td>Hide</td><td>NOT RESUME</td></row>
		<row><td>SetupResume</td><td>ResumeText</td><td>Show</td><td>RESUME</td></row>
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

