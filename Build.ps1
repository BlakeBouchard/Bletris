param ([switch] $Clean = $false, [switch] $Rebuild = $false)

if ($null -eq (Get-Command "nmake.exe" -ErrorAction SilentlyContinue))
{
	# This script will fail if it's not run from a Visual Studio Developer command line
	# If nmake is not on the path, we can assume that we need to enter the VS Command line
	$vsPath = &(Join-Path ${env:ProgramFiles(x86)} "\Microsoft Visual Studio\Installer\vswhere.exe") -property installationpath
	Write-Output "Using Visual Studio path: $vsPath"
	Import-Module (Get-ChildItem $vsPath -Recurse -File -Filter Microsoft.VisualStudio.DevShell.dll).FullName
	Enter-VsDevShell -VsInstallPath $vsPath -SkipAutomaticLocation
}

# We just want to run nmake here, and use the makefile for our complicated stuff
if ($Rebuild)
{
	Invoke-Expression "nmake rebuild"
}
elseif ($Clean)
{
	Invoke-Expression "nmake clean"
}
else
{
	Invoke-Expression "nmake"
}
