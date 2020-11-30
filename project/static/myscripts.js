// converters-related functions

function converterCmToInch(unit, valNum) {
    valNum = parseFloat(valNum);
    let cmInput = document.querySelector("#cmInput");
    let inchInput = document.querySelector("#inchInput");

    if (unit=="cmInput") {
        inchInput.value=(valNum*50/127).toFixed(2);
        if (cmInput.value.length == 0) {
            inchInput.value = "";
        }
    }

    if (unit=="inchInput") {
        cmInput.value=(valNum*127/50).toFixed(2);
        if (inchInput.value.length == 0) {
            cmInput.value = "";
        }
    }
}

function converterCmToFootInch(unit, valNum) {
    valNum = parseFloat(valNum);
    let cmInput_ = document.querySelector("#cmInput_");
    let footInput_ = document.querySelector("#footInput_");
    let inchInput_ = document.querySelector("#inchInput_");

    if (unit=="cmInput_") {
        footInput_.value = Math.floor((valNum*50/127).toFixed(2)/12);
        inchInput_.value = Math.round((valNum*50/127).toFixed(2)%12);
        if (cmInput_.value.length == 0) {
            footInput_.value = "";
            inchInput_.value = "";
        }
    }

    if (unit=="footInput_") {
        if (inchInput_.value.length == 0) {
            cmInput_.value = (valNum*1524/50).toFixed(2);
        }
        else {
            cmInput_.value= (valNum*1524/50 + parseFloat(inchInput_.value)*127/50).toFixed(2);
        }
        
        if (footInput_.value.length == 0) {
            if (inchInput_.value.length == 0) {
                cmInput_.value = "";
            }
            else {
                cmInput_.value = (parseFloat(inchInput_.value)*127/50).toFixed(2);
            }
        }
    }
    
    if (unit=="inchInput_") {
        if (footInput_.value.length == 0){
            cmInput_.value = (valNum*127/50).toFixed(2);
        }
        else {
            cmInput_.value= (parseFloat(footInput_.value)*1524/50 + valNum*127/50).toFixed(2);
        }
        if (inchInput_.value.length == 0) {
            if (footInput_.value.length == 0) {
                cmInput_.value = "";
            }
            else {
                cmInput_.value = parseFloat(footInput_.value)*1524/50;
            }
        }
    }
}

function converterMToYard(unit, valNum) {
    valNum = parseFloat(valNum);
    let mInput = document.querySelector("#mInput");
    let yardInput = document.querySelector("#yardInput");


    if (unit=="mInput") {
        yardInput.value=(valNum*5000/4572).toFixed(2);
        if (mInput.value.length == 0) {
            yardInput.value = "";
        }
    }

    if (unit=="yardInput") {
        mInput.value=(valNum*4572/5000).toFixed(2);
        if (yardInput.value.length == 0) {
            mInput.value = "";
        }
    }
}

function converterKmToMile(unit, valNum) {
    valNum = parseFloat(valNum);
    let kmInput = document.querySelector("#kmInput");
    let mileInput = document.querySelector("#mileInput");


    if (unit=="kmInput") {
        mileInput.value=(valNum*500000/804672).toFixed(2);
        if (kmInput.value.length == 0) {
            mileInput.value = "";
        }
    }

    if (unit=="mileInput") {
        kmInput.value=(valNum*804672/500000).toFixed(2);
        if (mileInput.value.length == 0) {
            kmInput.value = "";
        }
    }
}

function converterKgToPound(unit, valNum) {
    valNum = parseFloat(valNum);
    let kgInput = document.querySelector("#kgInput");
    let poundInput = document.querySelector("#poundInput");


    if (unit=="kgInput") {
        poundInput.value=(valNum*2.2046226218).toFixed(2);
        if (kgInput.value.length == 0) {
            poundInput.value = "";
        }
    }

    if (unit=="poundInput") {
        kgInput.value=(valNum/2.2046226218).toFixed(2);
        if (poundInput.value.length == 0) {
            kgInput.value = "";
        }
    }
}

function converterCToF(unit, valNum) {
    valNum = parseFloat(valNum);
    let cInput = document.querySelector("#cInput");
    let fInput = document.querySelector("#fInput");


    if (unit=="cInput") {
        fInput.value=Math.round((valNum*9/5+32));
        if (cInput.value.length == 0) {
            fInput.value = "";
        }
    }

    if (unit=="fInput") {
        cInput.value=Math.round((valNum-32)*5/9);
        if (fInput.value.length == 0) {
            cInput.value = "";
        }
    }
}


// todo-list related functions
if (localStorage.getItem("id") == null) {
    localStorage.setItem("id", 0);
}
let id = 0;

function newTask() {
    id = localStorage.getItem("id");
    let task;
    while (true) {
        task = prompt("Type what to do!");
        if (task == null) {
            return;
        }
        if (task.length != 0) {
            break;
        }
    }
    localStorage.setItem(id, task);
    
    let list = document.querySelector("#list");
    let li = document.createElement('li');
    let text = document.createTextNode(" " + task);
    li.setAttribute("id", id);
    li.setAttribute("class", "list-group-item");
    li.setAttribute("onclick", "deleteTask(this)")
    list.appendChild(li);
    li.appendChild(text);
    id++;
    localStorage.setItem("id", id);
}

function deleteTask(e) {
    document.getElementById(e.id).remove();
    localStorage.removeItem(e.id);
}

function clearAll() {
    for (let i = 0; i < localStorage.length; i++) {
        let k = localStorage.key(i);
        if (k != "id") {
            document.getElementById(k).remove();
        }
    }
    let temp = localStorage.getItem("id");
    localStorage.clear();
    localStorage.setItem("id", temp);
}

function resumeList() { 
    for (let i = 0; i < localStorage.length; i++) {
        let k = localStorage.key(i);
        if (k != "id") {
            let list = document.querySelector("#list");
            let li = document.createElement('li');
            let text = document.createTextNode(" " + localStorage.getItem(k));
            li.setAttribute("id", k);
            li.setAttribute("class", "list-group-item");
            li.setAttribute("onclick", "deleteTask(this)")
            list.appendChild(li);
            li.appendChild(text);        
        }
    }
}

