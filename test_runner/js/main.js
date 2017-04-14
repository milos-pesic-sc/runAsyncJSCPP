// Your code here!

test_runner = runner.Runner(function (e) {
    console.log("Callack invoked.");
})

function init() {
    test_runner.init();
}

function doSomethingHeavy() {
    test_runner.doSomethingHeavy();
}

document.addEventListener("DOMContentLoaded", function () {
    //add the event listeners for C++ component manipulation
    document.getElementById('Init').addEventListener('click', function () {
        test_runner.init();
    });
    document.getElementById('BlockUI').addEventListener('click', function () {
        test_runner,doSomethingHeavy();
    });
})

