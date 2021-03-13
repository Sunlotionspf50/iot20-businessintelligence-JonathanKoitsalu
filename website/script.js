let tabledata = document.getElementById('tabledata')

fetch("https://iot20-fa-jk.azurewebsites.net/api/GetLast10FromCosmosDB?")
.then(res => res.json())
.then(data => {
    for(let row of data){
        tabledata.innerHTML += `<tr><td>${row.id}</td><td>${row.deviceId}</td><td>${row.ts}</td><td>${row.temp}</td><td>${row.hum}</td>`
    }
})