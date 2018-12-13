import React, {Component} from 'react';
import {TextInput, Text, View, FlatList} from 'react-native';
import {Button} from 'native-base';
import DateTimePicker from 'react-native-modal-datetime-picker';

String.prototype.padStart = function padStart(x, y) {
  if (this.length < x) {
    return (y.toString().repeat((x - this.length))) + this;
  } else {
    return this.toString();
  }
};

export default class App extends Component{
  constructor(props){
    super(props);
    this.state = {
      isVisible: false,
      isVisible2: false,
      newTaskName:"",
      newTaskTime:{},
      taskList:[],
      duration: ''
    }
  }
/// Start Time:
  _showDateTimePicker = () => this.setState({ isVisible: true });

  _hideDateTimePicker = () => {
    this.setState({ isVisible: false });
  }

  _handleDatePicked = (date) => {
    this.setState({newTaskTime: date})
    this._hideDateTimePicker();
    this.addToList();
  };

  _handleDatePicked2 = (date) => {
    this.setState({newTaskTimeEnd: date})
    this._hideDateTimePicker2();
  };

  formatDate(){
    let taskDate = new Date(this.state.newTaskTime);

    let year = taskDate.getFullYear();
    let month = taskDate.getMonth() + 1;
    let day = taskDate.getDate();

    let dateString =  year.toString() + '-' +month.toString().padStart(2, 0) +'-'+day.toString().padStart(2, 0);
    return dateString;
  }

  formatTime(timee){
    let taskTime = new Date(timee);

    let hour = taskTime.getHours();
    let min = taskTime.getMinutes();
    let sec = taskTime.getSeconds();

    let timeString = hour.toString().padStart(2, 0) + ':'+min.toString().padStart(2, 0) +':'+ sec.toString().padStart(2, 0);
    return timeString;
  }

  formatDia(){
    let taskDate = new Date(this.state.newTaskTime);

    let year = taskDate.getFullYear();
    let month = taskDate.getMonth() + 1;
    let day = taskDate.getDate();

    let dateString =  day.toString().padStart(2, 0)+ '/' +month.toString().padStart(2, 0) +'/'+year.toString() ;
    return dateString;
  }

  addToList(){
    console.log('entrouuuuu')
    task = {
      name: this.state.newTaskName,
      dia: this.formatDia(),
      day: this.formatDate(),
      time: this.formatTime(this.state.newTaskTime),
      date: this.state.newTaskTime,
      duration: this.state.duration
    }
    let aux = this.state.taskList
    aux.push(task)
    this.setState({taskList: aux, newTaskName: ''})
    console.log('-----------')
    console.log(task);
    console.log('-----------')
  }

  render() {
    return (
      <View style = {styles.view}>
        <Text>Welcome to React Native!</Text>
        <FlatList
          data={this.state.taskList}
          keyExtractor = {(index) => index.toString()}
          extraData = {this.state}
          renderItem={({item}) => (
              <View style={{backgroundColor: 'grey'}}>
                <Text>{item.name}</Text>
                <Text>Data: {item.dia} Hora:{item.time}- Duração: {item.duration}</Text>
              </View>
          )}/>
        <TextInput
          placeholder = "Nova tarefa"
          style = {styles.input}
          onChangeText={(newTaskName) => (this.setState({newTaskName}))}
          value = {this.state.newTaskName}
        />
        <TextInput
          placeholder = "Tempo de duração"
          style = {styles.input}
          onChangeText={(duration) => (this.setState({duration}))}
          value = {this.state.duration}
        />
        <View style = {{flexDirection: 'row', justifyContent: 'space-between', marginBottom: 35, }}>
          <Button rounded onPress = {() => {this._showDateTimePicker()}} style = {styles.button}>
            <Text style={{color:"#FFF"}}> Adicionar nova tarefa </Text>
          </Button>
          <Button rounded onPress = {() => {}} style = {[styles.button, {backgroundColor: 'gray'}]}>
            <Text style={{color:"#FFF"}}> Gerar agenda </Text>
          </Button>
        </View>
        <DateTimePicker
          isVisible={this.state.isVisible}
          onCancel = {this._hideDateTimePicker}
          onConfirm = {this._handleDatePicked}
          mode = 'datetime'
        />
      </View>
    );
  }
}

const styles = {
  button:{
    backgroundColor: 'red',
    height: 30,
    width: 150,
    padding: 1,
  },
  view:{
    flex: 1,
    flexDirection: 'column',
    justifyContent: 'center',
    padding: 20
  },
  input:{
    borderColor:'red'
  }
}