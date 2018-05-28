#usage: powershell -file install_vs.ps1

function Installer {
    $installer = "C:\temp\vs_community.exe"
    $url = "https://aka.ms/vs/15/release/vs_community.exe"

    if (-not (Test-Path $installer)) {
        mkdir c:\temp
        Invoke-WebRequest -Uri $url -OutFile $installer    
    }

    return $installer
}

function Params
{
    return
        "--installPath", "C:\temp\minVS",
        "--nickname", "wde",
        "--add", "Microsoft.VisualStudio.Workload.WDExpress;Microsoft.VisualStudio.Workload.VCTools",
        "--passive",
        "--includeRecommended",
        "--norestart"
}

& $(Installer) $(Params)
