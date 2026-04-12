const STATE_WORKING  = 0
const STATE_ARRIVE   = 5
const STATE_CALL     = 10
const STATE_WAIT0    = 15
const STATE_WAIT1    = 16
const STATE_WAIT2    = 17
const STATE_STAIRS   = 20
const STATE_ENTER    = 25
const STATE_MOVE0    = 30
const STATE_MOVE1    = 31
const STATE_MOVE2    = 32
const STATE_GETOUT   = 35
const STATE_LEAVE    = 40

const TIME_ARRIVE   = 1000
const TIME_CALL     = 300
const TIME_ENTER    = 300
const TIME_GETOUT   = 300
const TIME_WAIT0    = 8000
const TIME_WAIT1    = 8000
const TIME_WAIT2    = 6000
const TIME_MOVE0    = 12000
const TIME_MOVE1    = 12000
const TIME_STAIRS   = 2000
const TIME_LEAVE    = 4000

const BTN_PRESSED   = true
const BTN_RELEASED  = false

const PRESENCE_DELTA  = -500

const PRESSURE_PER_KG = 1
const PRESSURE_ADD    = 1
const PRESSURE_REM    = -1

export default class Employee {
    #building
    #state = STATE_WORKING
    #floor
    #target = 0
    #time   = 0
    #li = null
    #weight
    #worktime
    #minWorkTime
    #maxWorkTime
    #character
    
    constructor(building, character, weight, minWorkTime, maxWorkTime) {
        this.#minWorkTime = minWorkTime
        this.#maxWorkTime = maxWorkTime
        this.#building = building
        this.#floor = Math.floor(Math.random()*building.floorCount())
        this.#worktime = Math.random() * (maxWorkTime - minWorkTime)
        this.#weight = weight
        this.#character = character
    }
    run(updatePeriod) {
        const self = this
        setInterval(() => self.#update(updatePeriod), updatePeriod)
    }
    #update(during) {
        switch(this.#state) {
            case STATE_WORKING:
                this.#waitBefore(STATE_ARRIVE, during, this.#worktime, ()=>{
                    const nfloors = this.#building.floorCount()

                    this.#target = (this.#floor + 1 + Math.floor(Math.random() * (nfloors - 1))) % nfloors
                    this.#addTo(this.#myFloorRoot(), '.corridor .waiting', true)
                })
                break
            case STATE_ARRIVE:
                if(this.#elapsed(during, TIME_ARRIVE) && !this.#tryEnter()) {
                    this.#state = STATE_CALL
                    this.#updateMood()
                    this.#callButton(BTN_PRESSED)
                }
                break
            case STATE_CALL:
                this.#waitBefore(STATE_WAIT0, during, TIME_CALL, () => {
                    this.#updateMood()
                    this.#callButton(BTN_RELEASED)
                });
                break
            case STATE_WAIT0: this.#tryEnter() || this.#waitBefore(STATE_WAIT1 , during, TIME_WAIT0, ()=>{
                    this.#updateMood()
                }); 
                break
            case STATE_WAIT1: this.#tryEnter() || this.#waitBefore(STATE_WAIT2 , during, TIME_WAIT1, ()=>{
                    this.#updateMood(true)
                }); 
                break
            case STATE_WAIT2: this.#tryEnter() || this.#waitBefore(STATE_STAIRS, during, TIME_WAIT2, () => {
                    this.#addTo(this.#myFloorRoot(), '.stairs ul', false, false)
                })
                break
            case STATE_ENTER:
                this.#waitBefore(STATE_MOVE0, during, TIME_ENTER, () => {
                    this.#cabinButton(BTN_RELEASED)
                    this.#building.endPass()
                })
                break
            case STATE_MOVE0: this.#tryGetOut(this.#target) || this.#waitBefore(STATE_MOVE1, during, TIME_MOVE0, ()=>{
                    this.#updateMood()
                }) 
                break
            case STATE_MOVE1: this.#tryGetOut(this.#target) || this.#waitBefore(STATE_MOVE2, during, TIME_MOVE1, ()=>{
                    this.#updateMood()
                })
                break
            case STATE_MOVE2: this.#tryGetOut(); break
            case STATE_GETOUT:
                const ok = this.#floor==this.#target

                this.#waitBefore(ok ? STATE_LEAVE : STATE_STAIRS, during, TIME_GETOUT, () => {
                    this.#building.endPass()
                    this.#updatePressure(PRESSURE_REM)
                    this.#addTo(this.#myFloorRoot(), ok ? '.corridor .exit':'.stairs ul', !ok, false)
                })
                break
            case STATE_LEAVE : this.#backToWork(during, TIME_LEAVE ); break
            case STATE_STAIRS: this.#backToWork(during, TIME_STAIRS); break
        }
    }
    #tryGetOut(target=undefined) {
        if(!this.#building.beginPass(target, PRESENCE_DELTA, 'presence')) 
            return false
        this.#floor = this.#building.elevatorFloor()
        if(this.#floor!=this.#target) {
            this.#updateMood(true)
        }
        this.#state = STATE_GETOUT
        return true
    }
    #waitBefore(nextState, delta, time, initStateCallback) {
        if(!this.#elapsed(delta, time)) return
        this.#state = nextState
        initStateCallback?.()
    }
    #backToWork(delta, time) {
        this.#waitBefore(STATE_WORKING, delta, time, () => {
            this.#worktime = this.#minWorkTime + 
                Math.random()*(this.#maxWorkTime - this.#minWorkTime)
            this.#addTo()
            this.#floor = this.#target
        })
    }
    #updatePressure(sign) {
        this.#building.analog(sign*PRESSURE_PER_KG*this.#weight, 'pressure')
    } 
    #callButton(pressed) {
        this.#building.button(
            pressed, 
            this.#floor < this.#target ? 'up' : 'down', 
            this.#floor
        )
    }
    #cabinButton(pressed) {
        this.#building.button(pressed, `cabin${this.#target}`)
    }
    #myFloorRoot() {
        return this.#building.floor(this.#floor)
    }
    #tryEnter() {
        const entered = this.#building.beginPass(
            this.#floor, PRESENCE_DELTA, 'presence', 
            () => this.#building.isCabinFull()
        )
        if(!entered) return false
        this.#state = STATE_ENTER
        this.#time = 0
        this.#addTo(this.#building.cabin())
        this.#updatePressure(PRESSURE_ADD)
        this.#cabinButton(BTN_PRESSED)
        return true
    }
    #elapsed(delta, duration) {
        this.#time += delta
        if(this.#time < duration) {
            return false;
        }
        this.#time -= duration 
        return true
    }
    #updateMood(showMood = false) {
        if(!this.#li) return
        let cssClass

        switch(this.#state) {
            case STATE_ARRIVE : case STATE_CALL  : cssClass = 'call'  ; break

            case STATE_MOVE0  : case STATE_WAIT0 : cssClass = 'wait0' ; break
            case STATE_MOVE1  : case STATE_WAIT1 : cssClass = 'wait1' ; break
            case STATE_MOVE2  : case STATE_WAIT2 : cssClass = 'wait2' ; break
            
            case STATE_STAIRS : cssClass = 'stairs'; break
            case STATE_ENTER  : cssClass = 'enter' ; break
            
            case STATE_WORKING:  
            case STATE_GETOUT : case STATE_LEAVE  : 
            default: cssClass = ''; break
        }
        this.#li.querySelector('span.mood').className = `mood ${cssClass} ${showMood?' show':''}`
    }
    #addTo(root = undefined, selector = 'ul', showMood = false, atEnd = true) {
        if(this.#li) {
            this.#li.remove()
            this.#li = null
        }
        if(root !== undefined) {
            const parent = root.querySelector(selector)
            
            this.#li = document.createElement('li');
            this.#li.innerHTML = `
                <span class="npc ch${this.#character.toString(16).toUpperCase()}"><a href='#'></a></span>
                <span class='mood'>${this.#building.floorTitle(this.#target)}</span>`
            if(atEnd)
                parent.appendChild(this.#li)
            else
                parent.insertBefore(this.#li, parent.firstChild)
            this.#updateMood(showMood)
        }
    }
}