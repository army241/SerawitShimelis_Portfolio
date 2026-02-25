let score=JSON.parse(localStorage.getItem('score')) || {
            wins: 0,
            loses: 0,
            ties: 0,
        };
        /*
    if (score===null){
        score={
            wins: 0,
            loses: 0,
            ties: 0,
        }
    }
            */
    
    console.log(localStorage.getItem('score'));
    function pickCompMove(){
        let randomNum=Math.random();
        let compMove='';
        if (randomNum>0 && randomNum<1/3){
            compMove='rock';
            
        } else if (randomNum>2/3 && randomNum<1){
            compMove='paper';
            
        } else if (randomNum>1/3 && randomNum<2/3){
            compMove='scissors';
            
        }
        return compMove;
    }
    let isAutoPlay=false;
    let intervalId;
    function autoPlay(){
        if (!isAutoPlay){
            intervalId=setInterval(function(){
            let playerMove=pickCompMove();
            playGame(playerMove);
        },1000);
        isAutoPlay=true;
        } else{
            clearInterval(intervalId);
            isAutoPlay=false;
        }
        
    }

    function playGame(playerMove){
        let compMove=pickCompMove();
        let result='';
        if (playerMove==="rock"){
                if (compMove==='rock'){
                    result=" Tie.";
            } else if (compMove==='paper'){
                result=" You lose.";
            } else if (compMove==='scissors'){
                result=" You win.";
            }
        } else if (playerMove==="paper") {
                if (compMove==='rock'){
                    result=" You win.";
            } else if (compMove==='paper'){
                result=" Tie.";
            } else if (compMove==='scissors'){
                result=" You lose.";
            }
        } else if (playerMove==="scissors"){
                if (compMove==='rock'){
                    result=" You lose.";
            } else if (compMove==='paper'){
                result=" You win.";
            } else if (compMove==='scissors'){
                result=" Tie.";
            }
        }
    if (result===" You win."){
        score.wins+=1
    } else if (result===" You lose."){
        score.loses+=1
    } else if (result===" Tie."){
        score.ties+=1
    };
    document.querySelector('.js-move')
        .innerHTML=`You <img src="${playerMove}.png">   <img src="${compMove}.png"> Computer`;
    document.querySelector('.js-result')
        .innerHTML= result;
    
    updateScore()
    localStorage.setItem('score',JSON.stringify(score));
    }
    function updateScore(){
        document.querySelector('.js-score')
        .innerHTML=`Wins: ${score.wins}, loses: ${score.loses}, ties: ${score.ties}`;
    }