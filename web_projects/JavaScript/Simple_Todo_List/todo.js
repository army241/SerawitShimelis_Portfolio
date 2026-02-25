const todoList=[
    {
        name: 'Go to the gym',
        dueDate: '2026-02-22',
    },
    {
        name: 'Watch Youtube',
        dueDate: '2026-02-23'
    }
];

function renderTodo(){
    let inputHtml ='';
    /*for (let i=0;i<todoList.length;i++){
        const todoObject=todoList[i];
        //const name=todoObject.name;
        //const dueDate=todoObject.dueDate;
        const {name,dueDate}=todoObject;
        const html=`
        <div>${name}</div>      
        <div>${dueDate}</div>
        <button onclick="
        todoList.splice(${i},1);
        renderTodo();
        "
        class="delete-button"
        >Delete</button>
        `;
        inputHtml+=html;
    }
    */
   todoList.forEach(function(todoObject,index){
    const {name,dueDate}=todoObject;
        const html=`
        <div>${name}</div>      
        <div>${dueDate}</div>
        <button onclick="
        todoList.splice(${index},1);
        renderTodo();
        "
        class="delete-button"
        >Delete</button>
        `;
        inputHtml+=html;
   })
    document.querySelector('.js-todo-list').innerHTML= inputHtml;
}


function addTodo(){
    let inputElement=document.querySelector('.js-todo-name');
    let dateInput=document.querySelector('.js-todo-date');
    let dueDate = dateInput.value;
    let name=inputElement.value;
    todoList.push({
        // name: name, dueDate: dueDate
        name,dueDate});
    
    inputElement.value='';
    renderTodo();
}

