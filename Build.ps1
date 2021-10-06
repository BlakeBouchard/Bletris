param ([switch] $Clean = $false, [switch] $Rebuild = $false, [switch] $Release = $false)

if ($IsWindows)
{
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
	if ($Clean)
	{
		Invoke-Expression "nmake clean"
	}
	elseif ($Release)
	{
		if ($Rebuild)
		{
			Invoke-Expression "nmake rebuild-release"
		}
		else
		{
			Invoke-Expression "nmake release"
		}
	}
	else
	{
		if ($Rebuild)
		{
			Invoke-Expression "nmake rebuild"
		}
		else
		{
			Invoke-Expression "nmake"
		}
	}
}
elseif ($IsMacos)
{
	if ($Release)
	{
		Write-Output "Release builds are not supported for MacOS. Building debug instead."
	}

	if ($Clean)
	{
		Invoke-Expression "make clean"
	}
	elseif ($Rebuild)
	{
		Invoke-Expression "make rebuild-macos"
	}
	else
	{
		Invoke-Expression "make build-macos"
	}
}
