const todoList=[
    
];
function renderTodo(){
    let inputHtml ='';
    for (let i=0;i<todoList.length;i++){
        const todo=todoList[i];
        const html=`<p>- ${todo}  
        <button onclick="
        todoList.splice(${i},1);
        renderTodo();
        "
        >Delete</button>
        </p>`;
        inputHtml+=html;
    }
    
    document.querySelector('.js-todo-list').innerHTML= inputHtml;
}


function addTodo(){
    let inputElement=document.querySelector('.js-todo-name');
    let name=inputElement.value;
    todoList.push(name);
    console.log(todoList);
    inputElement.value='';
    renderTodo();
}