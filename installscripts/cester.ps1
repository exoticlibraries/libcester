
$NAME="cester"
$DOWNLOAD_PATH="https://raw.githubusercontent.com/exoticlibraries/libcester/master/include/exotic/cester.h"
$Global:INSTALL_PATH=""
$AFTER_INSTALL_TEXT="compile your test like 'gcc -I. test.c', don't forget the -I. option"


Function Find-GCC-Include-Folder {
    # GCC
    $CmdOutput = cmd /c gcc -v '2>&1'
    ForEach ($Line in $CmdOutput) {
        if ($Line.Contains("/bin")) {
            return $Line.Split("bin")[0] + "bin"
        }
    }
}

Function Find-Include-Folder {
    $IncludePath_ = Find-GCC-Include-Folder
    $IncludePath = ""
    $previous_char = ''
    ForEach ($char in $IncludePath_.toCharArray()) {
        If ($char -eq ':') {
            $IncludePath += $previous_char
            $previous_char = '*'
        }
        if ($previous_char -eq "*") {
            $IncludePath += $char
        } else {
            $previous_char = $char
        }
    }
    if ($IncludePath.Contains("bin")) {
        Get-ChildItem -Path "$IncludePath/../" -Filter windows.h -Recurse | Foreach-Object { 
            $Global:INSTALL_PATH = [System.IO.Directory]::GetParent($_.FullName).FullName + "/exotic/"
        }
    }
}

Find-Include-Folder
"Downloading $NAME ..."
Invoke-WebRequest $DOWNLOAD_PATH -OutFile ./cester.h
"Installing lib$NAME into $Global:INSTALL_PATH"
if ($Global:INSTALL_PATH -eq "") {
    "Failed to detect the compiler include folder" 
    "cester.h downloaded into the current folder"
}
If ( -not [System.IO.Directory]::Exists($Global:INSTALL_PATH)) {
    [System.IO.Directory]::CreateDirectory($Global:INSTALL_PATH) > $null
    If ( -not $?) {
        "Failed to create the folder $($Global:INSTALL_PATH)." 
        "cester.h downloaded into the current folder"
        Return
    }
}
Move-Item -Path ./cester.h -Destination $Global:INSTALL_PATH -Force
$AFTER_INSTALL_TEXT
"Done installing $NAME"