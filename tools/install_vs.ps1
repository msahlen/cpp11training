
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
        "--add", "Microsoft.VisualStudio.Workload.CoreEditor",
        "--passive",
        "--norestart"
}

& $(Installer) $(Params)
