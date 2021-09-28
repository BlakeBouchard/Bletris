param ([switch] $Debug = $false)

$vsPath = &(Join-Path ${env:ProgramFiles(x86)} "\Microsoft Visual Studio\Installer\vswhere.exe") -property installationpath
Write-Output "Using Visual Studio path: $vsPath"
Import-Module (Get-ChildItem $vsPath -Recurse -File -Filter Microsoft.VisualStudio.DevShell.dll).FullName
Enter-VsDevShell -VsInstallPath $vsPath -SkipAutomaticLocation

if ($Debug)
{
	$buildDir = "./Debug"
}
else
{
	$buildDir = "./Output"
}

if (!(test-path $buildDir))
{
	New-Item -ItemType Directory -Force -Path $buildDir
}
Push-Location $buildDir
Invoke-Expression "cl.exe /Zi /FS /EHsc /nologo /Fe:'Bletris.exe' '..\src\cpp\*.cpp'"
Pop-Location
