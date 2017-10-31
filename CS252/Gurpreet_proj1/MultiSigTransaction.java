package in.ac.iitk.cse.cs252.transactions;

import org.bitcoinj.core.ECKey;
import org.bitcoinj.core.NetworkParameters;
import org.bitcoinj.core.Transaction;
import org.bitcoinj.core.Utils;
import org.bitcoinj.crypto.DeterministicKey;
import org.bitcoinj.crypto.TransactionSignature;
import org.bitcoinj.script.Script;
import org.bitcoinj.script.ScriptBuilder;

import java.io.File;
import java.math.BigInteger;

import static org.bitcoinj.script.ScriptOpCodes.*;

/**
 * Created by bbuenz on 24.09.15.
 */
public class MultiSigTransaction extends ScriptTransaction {
    // TODO: Problem 3
    private DeterministicKey bankKey;
    private DeterministicKey cust1key;
    private DeterministicKey cust2key;
    private DeterministicKey cust3key;
    public MultiSigTransaction(NetworkParameters parameters, File file, String password) {
        super(parameters, file, password);
        bankKey = getWallet().freshReceiveKey();
        cust1key = getWallet().freshReceiveKey();
        cust2key = getWallet().freshReceiveKey();
        cust3key = getWallet().freshReceiveKey();
    }

    @Override
    public Script createInputScript() {
        // TODO: Create a script that can be spend using signatures from the bank and one of the customers
        ScriptBuilder builder = new ScriptBuilder();
        builder.op(OP_SWAP);
        builder.data(bankKey.getPubKey());
        builder.op(OP_CHECKSIGVERIFY);
        builder.op(OP_1);
        builder.data(cust1key.getPubKey());
        builder.data(cust2key.getPubKey());
        builder.data(cust3key.getPubKey());
        builder.op(OP_3);
        builder.op(OP_CHECKMULTISIG);
        return builder.build();
        //return null;
    }

    @Override
    public Script createRedemptionScript(Transaction unsignedTransaction) {
        // Please be aware of the CHECK_MULTISIG bug!
        // TODO: Create a spending script
        TransactionSignature txSigbank = sign(unsignedTransaction, bankKey);
        TransactionSignature txSigcust1 = sign(unsignedTransaction, cust1key);
        TransactionSignature txSigcust2 = sign(unsignedTransaction, cust2key);
        TransactionSignature txSigcust3 = sign(unsignedTransaction, cust3key);

        ScriptBuilder builder = new ScriptBuilder();
        builder.op(OP_2);
        builder.data(txSigbank.encodeToBitcoin());
        builder.data(txSigcust1.encodeToBitcoin());
        return builder.build();
        //return null;
    }
}
