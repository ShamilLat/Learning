package main

var _ User = &superUser{}

type superUser struct {
	Name string
	Age  int
}

func (s *superUser) ChangeFIO(newFio string) {
	panic("implement me")
}

func (s *superUser) ChangeAddress(newAddress string) {
	panic("implement me")
}

// Подсказка, которая будет писать, что у нас не так
var _ User = &user{}

type user struct {
	FIO, Address, Phone string
}

func (u *user) ChangeFIO(newFio string) {
	u.FIO = newFio
}

func (u *user) ChangeAddress(newAddress string) {
	u.Address = newAddress
}

type User interface {
	ChangeFIO(newFio string)
	ChangeAddress(newAddress string)
}

func NewUser(fio, address, phone string) User {
	//u := user{
	//	FIO:     fio,
	//	Address: address,
	//	Phone:   phone,
	//}
	u := superUser{
		Name: "",
		Age:  0,
	}
	return &u
}

func main() {

}
