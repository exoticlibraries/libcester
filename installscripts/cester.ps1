
$NAME="cester"
$DOWNLOAD_PATH="https://raw.githubusercontent.com/exoticlibraries/libcester/main/include/exotic/cester.h"
$Global:IncludePaths = New-Object System.Collections.Generic.List[System.Object]
$AFTER_INSTALL_TEXT="compile your test like 'gcc -I. test.c', don't forget the -I. option"


Function Find-Include-Folder-With-Command {
    Param(
        [string]$command
    )

    $CmdOutput = cmd /c $command '2>&1'
    ForEach ($Line in $CmdOutput) {
        if ($Line.Contains("/bin") -or $Line.Contains("\bin")) {
            $IncludePath, $x = $Line -split ("bin") + "bin"
            $IncludePath = $IncludePath -split (":")
            $IncludePath = $IncludePath[$IncludePath.Length-1]
            $IncludePath = $Line.SubString($Line.IndexOf($IncludePath)-2, 2) + $IncludePath
            $IncludePath = ($IncludePath -split ("bin"))[0] + "bin"
        }
    }
    if (-not $IncludePath) {
        Return
    }
    Get-ChildItem -Path "$IncludePath/../" -Filter windows.h -Recurse | Foreach-Object { 
        $APath = [System.IO.Directory]::GetParent($_.FullName).FullName + "/exotic/"
    }
    # Barren C++ only compiler e.g CLANG
    If (-not $APath) {
        Get-ChildItem -Path "$IncludePath/../" -Filter stdbool.h -Recurse | Foreach-Object { 
            $APath = [System.IO.Directory]::GetParent($_.FullName).FullName + "/exotic/"
        }
    }
    If ($APath) {
        $Global:IncludePaths.Add($APath)
    }
}

Function Find-Include-Folder-With-Path {
    Param(
        [string]$path
    )

    Get-ChildItem -Path $path -Filter windows.h -Recurse -ErrorAction SilentlyContinue | Foreach-Object { 
        $APath = [System.IO.Directory]::GetParent($_.FullName).FullName + "/exotic/"
    }
    If (-not $APath) {
        Get-ChildItem -Path $path -Filter setjmp.h -Recurse -ErrorAction SilentlyContinue | Foreach-Object { 
            $APath = [System.IO.Directory]::GetParent($_.FullName).FullName + "/exotic/"
        }
    }
    If (-not $APath) {
        Get-ChildItem -Path $path -Filter stdbool.h -Recurse -ErrorAction SilentlyContinue | Foreach-Object { 
            $APath = [System.IO.Directory]::GetParent($_.FullName).FullName + "/exotic/"
        }
    }
    If ($APath) {
        $Global:IncludePaths.Add($APath)
    }
}

"Downloading $NAME ..."
New-Item -ItemType Directory -Path "./include/exotic/" -Force > $null
If ( -not $?) {
    "Failed to create the folder ./include/exotic/. Exiting..." 
    continue
}
Invoke-WebRequest $DOWNLOAD_PATH -OutFile ./include/exotic/cester.h
"Trying to detect headers paths ..."
Find-Include-Folder-With-Command "clang --version"
Find-Include-Folder-With-Command "gcc -v"
Find-Include-Folder-With-Path "C:\Program Files\Microsoft Visual Studio\"
Find-Include-Folder-With-Path "C:\Program Files (x86)\Microsoft Visual Studio\"
Find-Include-Folder-With-Path "C:\Program Files\LLVM\"
Find-Include-Folder-With-Path "C:\Program Files (x86)\LLVM\"
if ($($Global:IncludePaths).Length -eq 0) {
    "No compiler detected. cester.h downloaded into the current folder"
    Return
}
"Found $($($Global:IncludePaths).Length) compiler headers paths ..."
ForEach ($Path in $Global:IncludePaths) {
    If ( -not [System.IO.Directory]::Exists($Path)) {
        [System.IO.Directory]::CreateDirectory($Path) > $null
        If ( -not $?) {
            "Failed to create the folder $($Path). Skipping..." 
            continue
        }
    }
    " => Installing lib$NAME into $Path"
    Copy-Item -Path ./include/exotic/cester.h -Destination $Path -Force
}
"A copy is downloaded into the current directory"
$AFTER_INSTALL_TEXT
"Done installing $NAME"